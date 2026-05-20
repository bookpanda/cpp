#include "vector.h"
#include <cmath>
#include <iostream>
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

int main(void) {
    Vector v(3);
    v[2] = 2;
    cout << sqrt_sum(v) << '\n';
    f(v);
    return 0;
}