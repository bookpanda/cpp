#include <thread>

void do_something(int &i) { ++i; }

struct func {
    int &i;

    func(int &i_) : i(i_) {}

    void operator()() { // turns func into a function object (functor)
        for (unsigned j = 0; j < 1000000; ++j) {
            do_something(i);
        }
    }
};

void oops() {
    int some_local_state = 0; // dangling variable
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main() { oops(); }