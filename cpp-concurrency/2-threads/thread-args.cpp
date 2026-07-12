#include <string>
#include <thread>

void f(int i, std::string const &s);
void oops(int some_param) {
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    // by default, the arguments are copied into internal storage, where they can be accessed by the newly created
    // thread of execution,

    // even though f takes a std::string as the second parameter, the string literal is passed as a char const* and
    // converted to a std::string only in the context of the new thread.
    // oops() can exit before buffer is converted to a std::string on new thread
    // std::thread t(f, 3, buffer);

    // so we need to pass the string as a std::string
    std::thread t(f, 3, std::string(buffer));
    t.detach();
}

struct widget_id {
    int id;
};
struct widget_data {
    int data;
};
void display_status() {}
void process_widget_data(widget_data &data) {}

void update_data_for_widget(widget_id w, widget_data &data);
void oops_again(widget_id w) {
    widget_data data;
    // update_data_for_widget expects the second parameter to be passed by reference, the std::thread constructor
    // doesn’t know that
    // fail to compile because you can't pass an rvalue to a function that expects a non-const reference
    // std::thread t(update_data_for_widget, w, data);

    // std::ref will correctly pass a reference to data rather than a temporary copy of data
    std::thread t(update_data_for_widget, w, std::ref(data));
    display_status();
    t.join();
    process_widget_data(data);
}

// you can pass a member function pointer as the function, provided you supply a suitable object pointer as the first
// argument:
class X {
  public:
    void do_lengthy_work();
};
X my_x; // &my_x is the object pointer
std::thread t(&X::do_lengthy_work, &my_x);

// std::unique_ptr must be moved into the thread, not copied (only 1 unique_ptr can point to an obj at a time)
// std::unique_ptr is movable, but not copyable
// std::thread is also movable, but not copyable
class big_object {};
void process_big_object(std::unique_ptr<big_object> p) {}
std::unique_ptr<big_object> p(new big_object);
std::thread t2(process_big_object, std::move(p));