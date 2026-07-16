#include <memory>

// this can be made thread-safe by adding locks, and it's much better than the previous version:
template <typename T> class queue {
  private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    std::unique_ptr<node> head;
    node *tail;

  public:
    queue() : head(new node), tail(head.get()) {}
    queue(const queue &other) = delete;
    queue &operator=(const queue &other) = delete;
    // try_pop() now accesses tail only at beginning, so lock is short-lived
    std::shared_ptr<T> try_pop() {
        if (head.get() == tail) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(head->data);
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return res;
    }
    // push() now accesses only tail, no head
    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node); // create new dummy node
        tail->data = new_data;             // populate current dummy node with the new data
        node *const new_tail = p.get();
        tail->next = std::move(p);
        tail = new_tail;
    }
    // adding dummy node = try_pop() and push() are never operating on the same node, so you no longer need an
    // overarching mutex
    // - can have 1 mutex for head and 1 for tail
};