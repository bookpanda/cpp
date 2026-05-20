#include <iostream>
#include <list>
#include <string>

#include "vector.h"

template <typename T> class Less_than {
    const T val; // value to compare against
  public:
    Less_than(const T &v) : val(v) {}
    bool operator()(const T &x) const { return x < val; } // call operator
};

Less_than<int> lti{42};               // lti(i) will compare i to 42 using < (i<42)
Less_than<std::string> lts{"Backus"}; // lts(s) will compare s to "Backus" using < (s<"Backus")

void fct(int n, const std::string &s) {
    bool b1 = lti(n); // true if n<42
    bool b2 = lts(s); // true if s<"Backus"
    // ...
}

template <typename C, typename P> int count(const C &c, P pred) {
    int cnt = 0;
    for (const auto &x : c)
        if (pred(x))
            ++cnt;
    return cnt;
}

void f(const Vector<int> &vec, const std::list<std::string> &lst, int x, const std::string &s) {
    std::cout << "number of values less than " << x << ": " << count(vec, Less_than<int>{x}) << '\n';
    std::cout << "number of values less than " << s << ": " << count(lst, Less_than<std::string>{s}) << '\n';
}