#include <initializer_list>
class Vector {
  public:
    Vector(int s);
    Vector(std::initializer_list<double>); // initialize with a list of doubles
    double &operator[](int i);
    int size();
    void push_back(double); // add element at end, increasing the size by one
    ~Vector();

  private:
    double *elem; // elem points to an array of sz doubles
    int sz;
};