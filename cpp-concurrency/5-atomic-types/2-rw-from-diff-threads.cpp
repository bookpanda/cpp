#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// we don't want every item of data to be atomic (too expensive + restrictive)
std::vector<int> data;

// but we also don't want locks, so we use an atomic bool as flag to enforce ordering that write to data is before read
std::atomic<bool> data_ready(false);
void reader_thread() {
    while (!data_ready.load()) {
        // spin lock = bad
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "The answer = " << data[0] << "\n";
}
void writer_thread() {
    data.push_back(42);
    data_ready = true;
}