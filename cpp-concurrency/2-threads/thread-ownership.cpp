#include <iostream>
#include <thread>

void some_function() {
    while (true) {
        std::cout << "Thread ID: " << std::this_thread::get_id() << " - some_function" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void some_other_function() {
    while (true) {
        std::cout << "Thread ID: " << std::this_thread::get_id() << " - some_other_function" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::thread t1(some_function);
    std::thread t2 = std::move(t1);
    // t1 is now in a valid but unspecified state
    // t2 is now running some_function

    t1 = std::thread(some_other_function);
    // t1 is now running some_other_function

    std::thread t3;
    t3 = std::move(t2);
    // t2 is now in a valid but unspecified state
    // t3 is now running some_function

    t1 = std::move(t3);
    // t1 is already running some_other_function, so std::terminate() is called to terminate the whole program

    t1.join();
    t2.join();
    t3.join();

    return 0;
}