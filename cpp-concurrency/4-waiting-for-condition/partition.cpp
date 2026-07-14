#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 4, 9, 2, 8, 5, 7, 3};

    // Partition the vector so that all EVEN numbers come first
    auto boundary = std::partition(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; });

    // Output the partitioned vector
    std::cout << "Partitioned: ";
    for (int n : numbers)
        std::cout << n << " ";
    std::cout << "\n";

    // 'boundary' is an iterator pointing to the first element that failed the predicate (the first odd number)
    std::cout << "First odd number in partition: " << *boundary << "\n";
    // Partitioned: 8 4 2 9 1 5 7 3
    // First odd number in partition: 9 (boundary)
}