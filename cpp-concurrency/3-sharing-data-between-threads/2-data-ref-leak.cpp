#include <mutex>
#include <string>

class some_data {
    int a;
    std::string b;

  public:
    void do_something();
};

class data_wrapper {
  private:
    some_data data;
    std::mutex m;

  public:
    template <typename Function> void process_data(Function func) {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }
};

some_data *unprotected;
void malicious_function(some_data &protected_data) {
    // protected data's ref is leaked, mutex won't help
    unprotected = &protected_data;
}

data_wrapper x;
void foo() {
    x.process_data(malicious_function);
    unprotected->do_something(); // now the data is unprotected (not locked)
}