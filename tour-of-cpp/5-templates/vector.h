#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

template <typename T> class Vector {
  private:
    T *elem;
    // elem points to an array of sz elements of type T
    int sz;

  public:
    explicit Vector(int s);      // constructor: establish invariant, acquire resources
    ~Vector() { delete[] elem; } // destructor: release resources
    // ... copy and move operations ...
    T &operator[](int i);
    const T &operator[](int i) const;
    int size() const { return sz; }
    T *begin() const;
    T *end() const;
};

// template definitions belong to the header file
template <typename T> Vector<T>::Vector(int s) {
    if (s < 0)
        throw std::invalid_argument{"Vector size is negative"};
    elem = new T[s];
    sz = s;
}

template <typename T> T &Vector<T>::operator[](int i) {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

template <typename T> const T &Vector<T>::operator[](int i) const {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

template <typename T> T *begin(Vector<T> &x) {
    return x.size() ? &x[0] : nullptr;
    // pointer to first element or nullptr
}
template <typename T> T *end(Vector<T> &x) {
    return begin(x) + x.size(); // pointer to one-past-last element
}

template <typename T> T *Vector<T>::begin() const { return elem; }
template <typename T> T *Vector<T>::end() const { return elem + (size() * sizeof(T)); }

#endif