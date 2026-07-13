#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>

class data_chunk {
  public:
    data_chunk() {}
    data_chunk(std::string const &s) : s_(s) {}
    std::string s_;
};

bool more_data_to_prepare() { return true; }
data_chunk prepare_data() { return data_chunk(); }
void process(data_chunk &data) { std::cout << data.s_ << std::endl; }
bool is_last_chunk(data_chunk &data) { return data.s_ == "last_chunk"; }

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread() {
    while (more_data_to_prepare()) {
        data_chunk const data = prepare_data();
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(data);
        }
        // notify AFTER unlocking so that waiting thread doesn't immediately block again
        data_cond.notify_one();
    }
}
void data_processing_thread() {
    while (true) {
        // can't use lock_guard here because we need to unlock the mutex in the wait call
        std::unique_lock<std::mutex> lk(mut);

        data_cond.wait(lk, [] { return !data_queue.empty(); });
        // wait() checks condition
        // if true, returns. if false, unlocks mutex, puts thread to sleep, and waits for notification
        // when notified, wakes up, locks mutex, and checks condition again
        // if true, returns. if false, repeats the process

        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock(); // unlock after accessing data to allow other threads to access the queue
        // since process() doesn't touch the queue + takes time, we can unlock here
        process(data);
        if (is_last_chunk(data))
            break;
    }
}