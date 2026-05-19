#include <cstddef>
#include <iostream>

struct Vector {
    int sz;
    double *elem;
};

void vector_init(Vector &v, int s) {
    v.elem = new double[s]; // allocate an array of s doubles v.sz = s;
}

double read_and_sum(int s) // read s integers from cin and return their sum; s is assumed to be positive
{
    Vector v;
    vector_init(v, s);
    // // allocate s elements for v
    for (int i = 0; i != s; ++i)
        std::cin >> v.elem[i]; // read into elements
    double sum = 0;
    for (int i = 0; i != s; ++i)
        sum += v.elem[i]; // take the sum of the elements
    return sum;
}

int main(void) {
    Vector v;
    vector_init(v, 10);

    double sum = read_and_sum(10);
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}