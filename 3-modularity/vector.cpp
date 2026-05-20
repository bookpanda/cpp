#include "vector.h"
#include <algorithm>
#include <stdexcept>

Vector::Vector(int s) {
    if (s < 0)
        throw std::length_error{"Vector constructor: negative size"};
    elem = new double[s]{};
    sz = s;
}

Vector::Vector(std::initializer_list<double> lst) : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
    std::copy(lst.begin(), lst.end(), elem);
}

double &Vector::operator[](int i) {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

int Vector::size() const { return sz; }

// void Vector::push_back(double d) {
//     if (sz == cap())
//         reserve(cap() * 2);
//     elem[sz] = d;
//     sz++;
// }

Vector::~Vector() { delete[] elem; }

Vector_container::Vector_container(int s) : v(s) {} // Vector of s elements
Vector_container::Vector_container(std::initializer_list<double> lst) : v(lst) {}
Vector_container::~Vector_container() {}
double &Vector_container::operator[](int i) { return v[i]; }
int Vector_container::size() const { return v.size(); }