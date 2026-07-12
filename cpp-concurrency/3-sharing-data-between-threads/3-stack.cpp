#include <deque>
#include <exception>
#include <iostream>
#include <memory>
template <typename T, typename Container = std::deque<T>> class stack {
  public:
    explicit stack(const Container &);
    explicit stack(Container && = Container());
    template <class Alloc> explicit stack(const Alloc &);
    template <class Alloc> stack(const Container &, const Alloc &);
    template <class Alloc> stack(Container &&, const Alloc &);
    template <class Alloc> stack(stack &&, const Alloc &);
    bool empty() const;
    size_t size() const;
    T &top();
    T const &top() const;
    void push(T const &);
    void push(T &&);
    void pop();
    void swap(stack &&);
    template <class... Args> void emplace(Args &&...args);
};

struct empty_stack : std::exception {
    const char *what() const noexcept;
};
template <typename T> class threadsafe_stack {
  public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack &);
    threadsafe_stack &operator=(const threadsafe_stack &) = delete;
    void push(T new_value);
    // ways to prevent data race of having top() and pop() as split functions (internal mutex can't help if func calls
    // are separate aka can be interleaved with other threads)
    std::shared_ptr<T> pop(); // pop returns a shared_ptr to the value
    void pop(T &value);       // pop modifies the value by reference
    bool empty() const;
};

void do_something(const int &value) { std::cout << value << std::endl; }

int main() {
    stack<int> s;
    if (!s.empty()) {
        // problem: threads T1, T2 can call top() at same time (get same value), then call pop() twice
        // so the second value is never used, and the first value is used twice
        int const value = s.top();
        s.pop();
        do_something(value);
    }
    return 0;
}