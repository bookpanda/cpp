#include <barrier>
#include <thread>
#include <vector>

using namespace std;

struct data_chunk {
    int value;
};

struct data_block {
    int value;
};

struct data_sink {
    void write_data(data_chunk chunk);
};

struct result_chunk {
    int value;
};

struct result_block {
    data_chunk value;
    void set_chunk(unsigned i, unsigned num_threads, result_chunk chunk);
};

struct data_source {
    result_chunk process(data_chunk);
    std::vector<data_chunk> divide_into_chunks(data_block data, unsigned num_threads);
    void process_data(data_source &source, data_sink &sink) {
        unsigned const concurrency = std::thread::hardware_concurrency();
        unsigned const num_threads = (concurrency > 0) ? concurrency : 2;
        std::barrier sync(num_threads);
        std::vector<std::thread> threads(num_threads);
        std::vector<data_chunk> chunks;
        result_block result;
        for (unsigned i = 0; i < num_threads; ++i) {
            threads[i] = std::thread([&, i] {
                while (!source.done()) {
                    if (!i) {
                        data_block current_block = source.get_next_data_block();
                        chunks = divide_into_chunks(current_block, num_threads);
                    }
                    // important that no threads proceed until all threads are ready.
                    // everyone waiting for thread 0
                    sync.arrive_and_wait();
                    result.set_chunk(i, num_threads, process(chunks[i]));
                    // thread 0 waiting for all threads to finish processing their chunks
                    sync.arrive_and_wait();
                    if (!i) {
                        // thread 0 writes the result to the sink
                        sink.write_data(result.value);
                    }
                }
            });
        }
    }
    bool done() { return false; }
    data_block get_next_data_block() { return data_block{0}; }
};