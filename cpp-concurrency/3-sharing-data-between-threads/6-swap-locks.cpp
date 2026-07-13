#include <mutex>

class some_big_object {};
void swap(some_big_object &lhs, some_big_object &rhs);

class X {
  private:
    some_big_object some_detail;
    std::mutex m;

  public:
    X(some_big_object const &sd) : some_detail(sd) {}
    friend void swap(X &lhs, X &rhs) {
        if (&lhs == &rhs)
            return;
        // std::lock acquires both mutexes safely (e.g. try one, back off and retry if needed)
        // so it helps acquiring both locks without deadlock w/ other threads (lock ordering issue)
        // std::lock(lhs.m, rhs.m);
        // std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
        // std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
        // swap(lhs.some_detail, rhs.some_detail);

        // Alt w/ C++11's unique_lock (slower than lock_guard/scoped_lock but more flexible)
        // defer_lock means: “wrap this mutex in a unique_lock, but do not lock it yet.”
        // std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
        // std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
        // std::lock(lock_a, lock_b); // both locked safely (no ordering deadlock)
        // swap(lhs.some_detail, rhs.some_detail);

        // Alt w/ C++17's scoped_lock (basically same as std::lock_guard but for multiple locks)
        std::scoped_lock guard(lhs.m, rhs.m);
        swap(lhs.some_detail, rhs.some_detail);
    }
};