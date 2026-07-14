#include <iostream>
#include <list>

// The killer feature of splice() is its extreme efficiency:
// - Zero copies: No elements are copied.
// - Zero moves: No elements are moved.
// - Zero allocations: No heap memory is allocated or deallocated.
// - Time Complexity: $O(1)$ (constant time) for transferring a single element or an entire list.
// It achieves this simply by changing the next and prev pointers of the node boundary.
// It is a pure surgical redirection of pointers.

void print_list(const std::string &label, const std::list<int> &l) {
    std::cout << label << ": ";
    for (int x : l)
        std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::list<int> listA = {1, 2, 3, 4};
    std::list<int> listB = {10, 20, 30};

    // Scenario 1: Splice the ENTIRE listB into listA before '2'
    auto it = ++listA.begin(); // Points to '2'

    // Transfer all elements of B into A at position 'it'
    listA.splice(it, listB);

    std::cout << "--- After Splicing Entire List ---\n";
    print_list("listA", listA); // Outputs: 1 10 20 30 2 3 4
    print_list("listB", listB); // Outputs: (empty! listB is completely drained)

    // Scenario 2: Splice a single element back
    // Let's move '20' from listA back into listB
    listB.push_back(99); // listB is now {99}

    auto target_node = std::find(listA.begin(), listA.end(), 20);

    // Move '20' from listA into the beginning of listB
    listB.splice(listB.begin(), listA, target_node);

    std::cout << "\n--- After Splicing Single Element Back ---\n";
    print_list("listA", listA); // Outputs: 1 10 30 2 3 4 ('20' is gone)
    print_list("listB", listB); // Outputs: 20 99
}