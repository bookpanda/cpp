#include "vector.h"
#include <stdexcept>

template<typename T> Vector<T>::Vector(int s) {
    if (s < 0)
        throw std::invalid_argument{"Vector size is negative"};
    elem = new T[s];
    sz = s;
}
template<typename T> const T &Vector<T>::operator[](int i) const {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}