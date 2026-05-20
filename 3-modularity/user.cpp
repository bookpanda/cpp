#include "container.h"
#include "vector.h"
#include <cmath>
#include <iostream>
#include <numeric>
#include <stdexcept>

using namespace std;

void f(Vector &v) {
    try {
        v[v.size()] = 7; // try to access beyond the end of v
    } catch (std::out_of_range &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

double sqrt_sum(Vector &v) {
    double sum = 0;
    for (int i = 0; i != v.size(); ++i)
        sum += sqrt(v[i]); // sum of square roots
    return sum;
}

// noexcpet is a promise that the function will not throw an exception
// if it throws an exception, the program will terminate
void user(int sz) noexcept {
    Vector v(sz);
    iota(&v[0], &v[sz - 1], 1); // fill v with 1,2,3,4...
}

void test() {
    try {
        Vector v(-27);
    } catch (std::length_error &e) {
        // handle negative size
        std::cerr << "Error: " << e.what() << '\n';
        throw;                 // rethrow
    } catch (std::bad_alloc) { // handle memory exhaustion
        // If operator new can’t find memory to allocate, it throws a std::bad_alloc
        std::terminate(); // terminate the program
    }
}

constexpr double C = 299792.458;
void fs(double speed) {
    constexpr double local_max = 160.0 / (60 * 60);
    // static_assert(speed < C, "can't go that fast");     // error: speed must be a constant
    static_assert(local_max < C, "can't go that fast"); // OK  // ...
}

void use(Container &c) {
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        cout << c[i] << '\n';
}

void g() {
    Vector_container vc{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    use(vc);
}

int main(void) {
    Vector v(3);
    v[2] = 2;
    cout << sqrt_sum(v) << '\n';
    // f(v);
    user(10);
    // test();

    Vector v1 = {1, 2, 3, 4, 5};      // v1 has 5 elements
    Vector v2 = {1.23, 3.45, 6.7, 8}; // v2 has 4 elements
    return 0;
}