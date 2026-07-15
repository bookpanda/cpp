#include <atomic>
#include <iostream>

int main() {
    std::atomic<bool> x(false);
    bool expected = false;
    while (!x.compare_exchange_weak(expected, true) && !expected)
        ;
    std::cout << x.load(std::memory_order_relaxed) << std::endl; // 1
    std::cout << expected << std::endl;                          // 0

    // x.store(true, std::memory_order_relaxed);

    std::atomic<bool> b;
    // mem_ord_if_success, mem_ord_if_failure
    b.compare_exchange_weak(expected, true, std::memory_order_acq_rel, std::memory_order_acquire);
    // if you don't specify failure mem order, it uses success mem order, but strips the "release" part, so this failure
    // mem order is std::memory_order_acquire
    b.compare_exchange_weak(expected, true, std::memory_order_acq_rel);
    return 0;
}