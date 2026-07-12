// std::future and std::promise are the two halves of an asynchronous communication channel. They act as a
// synchronization pipeline for passing a value (or an exception) from one thread to another without you having to
// manually write mutexes, condition variables, or shared state flags.

// std::promise is the input end: It is a commitment made by the producer thread to deliver a result at some point in
// the future.

// std::future is the output end: It is a placeholder held by the consumer thread to retrieve that result once it
// becomes available.

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void computeResult(std::promise<int> resultPromise) {
    // Simulating a heavy systems computation or network I/O
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    int calculatedValue = 42;

    // Fulfill the promise. This wakes up anyone blocking on the future.
    resultPromise.set_value(calculatedValue);
}

int main() {
    std::promise<int> myPromise;

    // get the associated future from the promise
    std::future<int> myFuture = myPromise.get_future();

    // move the promise into a background thread
    // (Promises must be moved, they cannot be copied)
    std::thread worker(computeResult, std::move(myPromise));

    std::cout << "Doing other work in main thread...\n";

    // block until the background thread calls set_value()
    int result = myFuture.get();
    std::cout << "Result received from thread: " << result << "\n";

    worker.join();
    return 0;
}