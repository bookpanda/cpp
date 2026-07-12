#include <deque>
#include <exception>
#include <iostream>
#include <memory>
#include <stack>
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
    const char *what() const throw();
};
template <typename T> class threadsafe_stack {
  private:
    std::stack<T> data;
    mutable std::mutex m;

  public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack &other) {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    threadsafe_stack &operator=(const threadsafe_stack &) = delete;
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }
    // ways to prevent data race of having top() and pop() as split functions (internal mutex can't help if func calls
    // are separate aka can be interleaved with other threads)
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T &value) {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        value = data.top();
        data.pop();
    }
    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    };
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