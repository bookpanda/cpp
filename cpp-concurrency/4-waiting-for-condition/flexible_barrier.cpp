#include <barrier>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    int stage = 1;

    // Define the custom completion function (the "flexible" part)
    auto on_phase_completion = [&stage]() noexcept {
        std::cout << "--- Stage " << stage << " Completed ---\n";
        stage++;
    };

    // Pass the lambda type as the template parameter
    std::barrier<decltype(on_phase_completion)> flexible_barrier(3, on_phase_completion);

    auto worker = [&](int id) {
        std::cout << "Thread " << id << " working on Stage 1...\n";
        flexible_barrier.arrive_and_wait(); // Sync point 1 (triggers completion function)

        std::cout << "Thread " << id << " working on Stage 2...\n";
        flexible_barrier.arrive_and_wait(); // Sync point 2 (triggers completion function)
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto &t : threads) {
        t.join();
    }
}