#include <future>
#include <string>

struct X {
    void foo(int, std::string const &);
    std::string bar(std::string const &);
};

X x;
auto f1 = std::async(&X::foo, &x, 42, "hello");
auto f2 = std::async(&X::bar, x, "goodbye");

struct Y {
    double operator()(double);
};

Y y;
auto f3 = std::async(Y(), 3.141);
auto f4 = std::async(std::ref(y), 2.718);

X baz(X &);
auto f6 = std::async(baz, std::ref(x));

class move_only {
  public:
    move_only();
    move_only(move_only &&);
    move_only(move_only const &) = delete;
    move_only &operator=(move_only &&);
    move_only &operator=(move_only const &) = delete;
    void operator()();
};
auto f5 = std::async(move_only());

int main() {
    // launch::async = func must be run on its own thread
    auto f67 = std::async(std::launch::async, Y(), 1.2);
    // launch::deferred = func is executed when .wait()/.get() is called
    auto f7 = std::async(std::launch::deferred, baz, std::ref(x));
    // default = either
    auto f8 = std::async(std::launch::deferred | std::launch::async, baz, std::ref(x));
    auto f9 = std::async(baz, std::ref(x));
    f7.wait();
}