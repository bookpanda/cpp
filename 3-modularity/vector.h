#ifndef VECTOR_H
#define VECTOR_H

#include "container.h"
#include <initializer_list>

class Vector {
  public:
    Vector(int s);
    Vector(std::initializer_list<double>); // initialize with a list of doubles
    double &operator[](int i);
    int size() const;
    // void push_back(double); // add element at end, increasing the size by one
    ~Vector();

  private:
    double *elem; // elem points to an array of sz doubles
    int sz;
};

class Vector_container : public Container { // Vector_container implements Container
    Vector v;

  public:
    Vector_container(int s);
    Vector_container(std::initializer_list<double>);
    ~Vector_container();
    double &operator[](int i);
    int size() const;
};

#endif // VECTOR_H