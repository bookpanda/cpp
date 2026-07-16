#include <condition_variable>
#include <functional>
#include <mutex>

class Foo {
  private:
    std::condition_variable cv;
    std::mutex mut;
    int count;

  public:
    Foo() : count(0) {}

    void first(std::function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        count++;
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lk(mut);
        cv.wait(lk, [this] { return count == 1; });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        count++;
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lk(mut);
        cv.wait(lk, [this] { return count == 2; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};