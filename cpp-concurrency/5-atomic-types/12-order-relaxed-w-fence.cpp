#include <assert.h>
#include <atomic>
#include <thread>

// if non-atomic op A is sequenced before atomic op B, and op B is happens before op C on another thread,
// then op A happens before op C

// x can be non-atomic since fences still enforce ordering: store_x -> store_y and load_y -> load_x
// and there's no data race on x
std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y() {
    x.store(true, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
    // load_y is guaranteed to see result of store_y since it loops until it sees true (store_y -> load_y)
    // load_y (acq) sees result of a store after a release fence, so release fence -> load_y (syncs-with)
    // load_y is before acquire fence and sees result of store_y (release), so store_y -> acquire fence (syncs-with)
    // total:  release fence -> store_y -> load_y -> acquire fence -> load_x
    while (!y.load(std::memory_order_relaxed))
        ;
    std::atomic_thread_fence(std::memory_order_acquire);
    if (x.load(std::memory_order_relaxed))
        ++z;
}

int main() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0);
}