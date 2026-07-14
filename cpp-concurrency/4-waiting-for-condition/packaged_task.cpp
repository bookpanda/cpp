#include <future>
#include <iostream>
#include <thread>

int calculate_square(int x) { return x * x; }

int main() {
    // Wrap the function. Note the template signature matches the function.
    std::packaged_task<int(int)> task(calculate_square);
    std::future<int> my_future = task.get_future();

    // You must manually invoke the task (or pass it to a thread)
    std::thread t(std::move(task), 5);

    std::cout << "packaged_task: " << my_future.get() << std::endl; // Outputs 25
    t.join();
}