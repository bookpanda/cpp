#include <iostream>
#include <list>
#include <string>
#include <vector>

// alias generic iterator
template <typename T> using Iterator = typename T::iterator; // T’s iterator

template <typename C, typename V>
std::vector<Iterator<C>> find_all(C &c, V v) // find all occurrences of v in c
{
    std::vector<Iterator<C>> res;
    for (auto p = c.begin(); p != c.end(); ++p)
        if (*p == v)
            res.push_back(p);
    return res;
}

void test() {
    std::string m{"Mary had a little lamb"};
    for (auto p : find_all(m, 'a'))
        // p is a string::iterator
        if (*p != 'a')
            std::cerr << "string bug!\n";
    std::list<double> ld{1.1, 2.2, 3.3, 1.1};
    for (auto p : find_all(ld, 1.1))
        if (*p != 1.1)
            std::cerr << "list bug!\n";
    std::vector<std::string> vs{"red", "blue", "green", "green", "orange", "green"};
    for (auto p : find_all(vs, "red"))
        if (*p != "red")
            std::cerr << "vector bug!\n";

    for (auto p : find_all(vs, "green"))
        *p = "vert";
}

int main(void) {
    test();
    return 0;
}