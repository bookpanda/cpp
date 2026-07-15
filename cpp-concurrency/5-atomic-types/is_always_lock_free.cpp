#include <atomic>
// #include <iostream>

int main() {
    std::atomic<int>::is_always_lock_free;
    ATOMIC_INT_LOCK_FREE;
    std::atomic<bool>::is_always_lock_free;
    ATOMIC_BOOL_LOCK_FREE;
    // std::atomic<int> x(0);
    // std::cout << std::atomic_is_lock_free(&x) << std::endl;
    return 0;
}