#include <future>
#include <iostream>

int calculate_meaning_of_life() { return 42; }

int main() {
    // No manual threads, no manual promises, no manual task execution.
    std::future<int> my_future = std::async(calculate_meaning_of_life);

    std::cout << "async: " << my_future.get() << std::endl;
}