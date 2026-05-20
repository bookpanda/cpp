#include "shape.h"
#include <iostream>

enum class Kind { circle, triangle, smiley };
Shape *read_shape(std::istream &is) // read shape descriptions from input stream is
{
    Kind k;
    // ... read shape header from is and find its Kind k ...
    switch (k) {
    case Kind::circle: // read circle data {Point,int} into p and r
        Point p;
        int r;
        return new Circle{p, r};
    case Kind::triangle: // read triangle data {Point,Point,Point} into p1, p2, and p3
        return new Triangle{Point{0, 0}, Point{1, 0}, Point{0, 1}};
    case Kind::smiley: // read smiley data {Point,int,Shape,Shape,Shape} into p, r, e1 ,e2, and
        Smiley *ps = new Smiley{Point{0, 0}, 1};
        ps->add_eye(new Circle{Point{0, 0}, 1});
        ps->add_eye(new Circle{Point{0, 0}, 1});
        ps->set_mouth(new Circle{Point{0, 0}, 1});
        return ps;
    }
}

int main(void) {
    Shape *ps{read_shape(std::cin)};
    if (Smiley *p = dynamic_cast<Smiley *>(ps)) {
        // ... is the Smiley pointer to by p ...
    } else {
        // ... not a Smiley, try something else ...
    }
    return 0;
}