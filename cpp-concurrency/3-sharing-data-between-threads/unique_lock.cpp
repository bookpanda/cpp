#include <mutex>

std::mutex some_mutex;

void prepare_data() {
    // prepare data
}

void do_something() {
    // do something
}

std::unique_lock<std::mutex> get_lock() {
    extern std::mutex some_mutex;
    std::unique_lock<std::mutex> lk(some_mutex);
    prepare_data();
    return lk;
}
void process_data() {
    // unique_lock is movable but not copyable
    // so we can have a func lock a mutex and transfer ownsership of lock to the caller
    // caller can then perform additional actions under same lock
    // when caller finishes, lock is automatically unlocked
    std::unique_lock<std::mutex> lk(get_lock());
    do_something();
}

class some_class {
  public:
    some_class() {}
    some_class(const some_class &) = delete;
    some_class &operator=(const some_class &) = delete;
};

class result_type {
  public:
    result_type() {}
    result_type(const result_type &) = delete;
    result_type &operator=(const result_type &) = delete;
};

some_class get_next_data_chunk() { return some_class(); }

void write_result(some_class &data, result_type &result) {
    // write result
}

result_type process(some_class &data) { return result_type(); }

void get_and_process_data() {
    // unique_lock works well when we need to lock/unlock multiple times
    std::unique_lock<std::mutex> my_lock(some_mutex);
    some_class data_to_process = get_next_data_chunk();
    my_lock.unlock();
    // processing phase: unlock to avoid deadlock + better performance since other threads can operate on the data
    result_type result = process(data_to_process);
    my_lock.lock(); // re-lock
    write_result(data_to_process, result);
}