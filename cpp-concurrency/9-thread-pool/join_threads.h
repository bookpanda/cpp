#ifndef JOIN_THREADS_H
#define JOIN_THREADS_H

#include <atomic>
#include <thread>
#include <vector>

class join_threads {
    std::vector<std::thread> &threads;
    std::atomic_bool done;

  public:
    join_threads(std::vector<std::thread> &threads_) : threads(threads_), done(false) {}
    join_threads(const join_threads &) = delete;
    join_threads &operator=(const join_threads &) = delete;
    ~join_threads() {
        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }
};

#endif