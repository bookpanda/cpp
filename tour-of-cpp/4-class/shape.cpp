#include "shape.h"
#include <vector>

void rotate_all(std::vector<Shape *> &v, int angle) // rotate v’s elements by angle degrees
{
    for (auto p : v)
        p->rotate(angle);
}

void Smiley::draw() const {
    Circle::draw();
    for (auto p : eyes)
        p->draw();
    mouth->draw();
}