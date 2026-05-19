#include <iostream>

struct Vector {
  int sz;
  double *elem;
};

void vector_init(Vector &v, int s) {
  v.elem = new double[s]; // allocate an array of s doubles v.sz = s;
}

int main(void) {}