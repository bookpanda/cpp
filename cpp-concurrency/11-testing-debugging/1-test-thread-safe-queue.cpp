#include <cassert>
#include <future>

void test_concurrent_push_and_pop_on_empty_queue() {
    threadsafe_queue<int> q;
    std::promise<void> go, push_ready, pop_ready;
    std::shared_future<void> ready(go.get_future());
    std::future<void> push_done;
    std::future<int> pop_done;

    try {
        // launch 2 threads to push and pop from the queue
        push_done = std::async(std::launch::async, [&q, ready, &push_ready]() {
            push_ready.set_value(); // signal to main that push thread is ready
            ready.wait();           // wait for main's signal to start
            q.push(42);
        });

        pop_done = std::async(std::launch::async, [&q, ready, &pop_ready]() {
            pop_ready.set_value(); // signal to main that pop thread is ready
            ready.wait();          // wait for main's signal to start
            return q.pop();
        });

        // wait for both threads to be ready
        push_ready.get_future().wait();
        pop_ready.get_future().wait();

        // signal to start
        go.set_value();
        push_done.get(); // wait for push thread to finish
        assert(pop_done.get() == 42);
        assert(q.empty());
    } catch (...) {
        go.set_value();
        throw;
    }
}