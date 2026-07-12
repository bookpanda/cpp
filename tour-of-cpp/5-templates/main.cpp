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

template <typename T> void g(T x) { std::cout << x << " "; }
void f() {} // do nothing

template <typename T, typename... Tail> void f(T head, Tail... tail) {
    g(head);    // do something to head
    f(tail...); // try again with tail
}

int main(void) {
    Vector<int> v(10);

    std::cout << "first: ";
    f(1, 2.2, "hello");
    std::cout << "\nsecond: ";
    f(0.2, 'c', "yuck!", 0, 1, 2);
    std::cout << "\n";
    return 0;
}

// alias template (using)
template <typename C> using Element_type = typename C::value_type; // the type of C’s elements
template <typename Container> void algo(Container &c) {
    Vector<Element_type<Container>> vec;
    // keep results here // ...
}

template <typename Key, typename Value> class Map {};

template <typename Value> using String_map = Map<std::string, Value>;

String_map<int> m; // m is a Map<std::string,int>
