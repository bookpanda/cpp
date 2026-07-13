#include <future>

class connection_id {
  public:
    int id;
};

class payload_type {
  public:
    int payload;
};

class data_packet {
  public:
    connection_id id;
    payload_type payload;
};

class outgoing_packet {
  public:
    connection_id id;
    payload_type payload;
    std::promise<bool> promise;
};

class connection {
  public:
    bool has_incoming_data();
    data_packet incoming();
    bool has_outgoing_data();
    outgoing_packet top_of_outgoing_queue();
    void send(payload_type data);
    std::promise<payload_type> get_promise(connection_id id);
};

class connection_iterator {
  public:
    bool operator!=(connection_iterator other);
    connection &operator*();
    connection_iterator &operator++();
    connection *operator->();
};

class connection_set {
  public:
    bool done();
    connection_iterator begin();
    connection_iterator end();
    connection *get_connection(connection_id id);
    std::promise<payload_type> get_promise(connection_id id);
};

void process_connections(connection_set &connections) {
    while (!connections.done()) {
        for (connection_iterator connection = connections.begin(), end = connections.end(); connection != end;
             ++connection) {
            if (connection->has_incoming_data()) {
                data_packet data = connection->incoming();
                std::promise<payload_type> p = connection->get_promise(data.id);
                p.set_value(data.payload);
            }
            if (connection->has_outgoing_data()) {
                outgoing_packet data = connection->top_of_outgoing_queue();
                connection->send(data.payload);
                data.promise.set_value(true);
            }
        }
    }
}