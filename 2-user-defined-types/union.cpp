#include <iostream>

enum Type { str, num };

union Value {
    char *s;
    int i;
};

struct Entry {
    char *name;
    Type t;
    Value v; // use v.s if t==str; use v.i if t==num
};
void f(Entry *p) {
    // The language doesn’t keep track of which kind of value is held by a union, so the programmer must do that
    // tho can use tagged union to achieve this
    if (p->t == str)
        std::cout << p->v.s; // ...
}

int main(void) {
    Entry e;
    e.name = "hello";
    e.t = str;
    e.v.s = "hello";
    f(&e);
    return 0;
}