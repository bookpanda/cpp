#include "vector.h"
#include <algorithm>
#include <stdexcept>

Vector::Vector(int s) {
    if (s < 0)
        throw std::length_error{"Vector constructor: negative size"};
    elem = new double[s]{};
    sz = s;
}

Vector::Vector(std::initializer_list<double> lst) {
    elem = new double[lst.size()];
    std::copy(lst.begin(), lst.end(), elem);
    sz = static_cast<int>(lst.size());
}

double &Vector::operator[](int i) {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

int Vector::size() { return sz; }

// void Vector::push_back(double d) {
//     if (sz == cap())
//         reserve(cap() * 2);
//     elem[sz] = d;
//     sz++;
// }

Vector::~Vector() { delete[] elem; }