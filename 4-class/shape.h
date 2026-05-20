#include <iostream>
#include <vector>

#ifndef SHAPE_H
#define SHAPE_H

class Point {
  public:
    int x;
    int y;
};

class Shape {
  public:
    virtual Point center() const = 0; // pure virtual virtual
    virtual void move(Point to) = 0;
    virtual void draw() const = 0; // draw on current "Canvas"
    virtual void rotate(int angle) = 0;
    virtual ~Shape() {} // destructor // ...
};

class Circle : public Shape {
  public:
    Circle(Point p, int rr); // constructor
    Point center() const override { return x; }
    void move(Point to) override { x = to; }
    void draw() const override { std::cout << "Circle\n"; }
    void rotate(int angle) override { std::cout << "Circle rotate\n"; }
    ~Circle() override {}

  private:
    Point x;
    int r;
};

class Triangle : public Shape {
  public:
    Triangle(Point p1, Point p2, Point p3); // constructor
    Point center() const override { return Point{(p1.x + p2.x + p3.x) / 3, (p1.y + p2.y + p3.y) / 3}; }
    void move(Point to) override {
        p1 = to;
        p2 = to;
        p3 = to;
    }
    void draw() const override { std::cout << "Triangle\n"; }
    void rotate(int angle) override { std::cout << "Triangle rotate\n"; }
    ~Triangle() override {}

  private:
    Point p1;
    Point p2;
    Point p3;
};

class Smiley : public Circle { // use the circle as the base for a face
  public:
    Smiley(Point p, int r) : Circle{p, r}, mouth{nullptr} {}
    ~Smiley() {
        delete mouth;
        for (auto p : eyes)
            delete p;
    }
    void move(Point to) override;
    void draw() const override;
    void rotate(int) override;
    void add_eye(Shape *s) { eyes.push_back(s); }
    void set_mouth(Shape *s);
    virtual void wink(int i); // wink eye number i // ...
  private:
    std::vector<Shape *> eyes; // usually two eyes
    Shape *mouth;
};

#endif // SHAPE_H