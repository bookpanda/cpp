#include "vector.h"
#include <iostream>

void write(const Vector<std::string> &vs) // Vector of some strings
{
    for (int i = 0; i != vs.size(); ++i)
        std::cout << vs[i] << '\n';
}

void f2(Vector<std::string> &vs) // Vector of some strings
{
    for (auto &s : vs)
        std::cout << s << '\n';
}

template <typename Container, typename Value> Value sum(const Container &c, Value v) {
    for (auto x : c)
        v += x;
    return v;
}

int main(void) {
    Vector<int> v(10);
    return 0;
}