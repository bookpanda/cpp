#include <future>
#include <iostream>
#include <thread>

void compute(std::promise<int> output_promise) {
    // Do some heavy lifting
    int result = 42;
    output_promise.set_value(result); // Manually push the result
}

int main() {
    std::promise<int> my_promise;
    std::future<int> my_future = my_promise.get_future();

    std::thread t(compute, std::move(my_promise)); // Must move promise

    std::cout << "promise: " << my_future.get() << std::endl; // Blocks until set_value is called
    t.join();
}