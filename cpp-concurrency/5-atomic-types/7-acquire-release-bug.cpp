#include <assert.h>
#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x() { x.store(true, std::memory_order_release); }
void write_y() { y.store(true, std::memory_order_release); }
void read_x_then_y() {
    while (!x.load(std::memory_order_acquire))
        ;
    if (y.load(std::memory_order_acquire))
        ++z;
}

void read_y_then_x() {
    while (!y.load(std::memory_order_acquire))
        ;
    if (x.load(std::memory_order_acquire))
        ++z;
}

int main() {
    x = false;
    y = false;
    z = 0;
    // acq/rel mem ord enforces only these happens-before:
    // 1. write_x happens-before read_x_then_y
    // 2. write_y happens-before read_y_then_x
    // So,
    // read_x_then_y can happen before write_y and read_y_then_x can happen before write_x
    // causing assert to fail or z < 2
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    std::thread a(write_x);
    std::thread b(write_y);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load() != 2);
    cout << "z: " << z.load() << endl;
}