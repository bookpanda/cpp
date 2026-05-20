#include <condition_variable>
#include <mutex>
#include <queue>

class Message { // object to be communicated
    // ...
};

std::queue<Message> mqueue;    // the queue of messages
std::condition_variable mcond; // the variable communicating events
std::mutex mmutex;             // the locking mechanism

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lck{mmutex}; // acquire mmutex

        mcond.wait(lck, [] { return !mqueue.empty(); }); // release lck and wait;
        // re-acquire lck upon wakeup

        // mcond.wait(lck, [] { return !mqueue.empty(); }); will expand to:
        // while (!([] { return !mqueue.empty(); })()) {
        //     mcond.wait(lck);
        // }

        auto m = mqueue.front(); // get the message
        mqueue.pop();
        lck.unlock(); // release lck
        // ... process m ...
    }
}

void producer() {
    while (true) {
        Message m;
        // ... fill the message ...

        {
            // Unlock the mutex before notifying to ensure that when the consumer wakes up, the lock is wide open for
            // the taking.
            std::lock_guard<std::mutex> lck{mmutex}; // lock_guard is sufficient here
            mqueue.push(m);
        } // <--- Lock is explicitly released here as scope ends
        // std::unique_lock<std::mutex> lck{mmutex}; // protect operations
        // mqueue.push(m);

        mcond.notify_one(); // notify
                            // release lock (at end of scope)
    }
}