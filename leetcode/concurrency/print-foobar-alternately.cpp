#include <condition_variable>
#include <functional>
#include <mutex>

class FooBar {
  private:
    int n;
    std::condition_variable cv;
    std::mutex mut;
    bool state;

  public:
    FooBar(int n) {
        this->n = n;
        this->state = true;
    }

    void foo(std::function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lk(mut);
            cv.wait(lk, [this] { return state; });
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            state = false;
            cv.notify_one();
        }
    }

    void bar(std::function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lk(mut);
            cv.wait(lk, [this] { return !state; });
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            state = true;
            cv.notify_one();
        }
    }
};