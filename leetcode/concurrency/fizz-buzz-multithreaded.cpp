#include <condition_variable>
#include <functional>
#include <mutex>

class FizzBuzz {
  private:
    int n;
    std::condition_variable cv;
    std::mutex mut;
    // std::atomic<int> count{1};
    int count = 1;

  public:
    FizzBuzz(int n) { this->n = n; }

    // printFizz() outputs "fizz".
    void fizz(std::function<void()> printFizz) {
        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5 != 0) {
                std::unique_lock lk(mut);
                cv.wait(lk, [this, i] { return this->count == i; });
                printFizz();
                count++;
                lk.unlock();
                cv.notify_all();
            }
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(std::function<void()> printBuzz) {
        for (int i = 1; i <= n; i++) {
            if (i % 3 != 0 && i % 5 == 0) {
                std::unique_lock lk(mut);
                cv.wait(lk, [this, i] { return this->count == i; });
                printBuzz();
                count++;
                lk.unlock();
                cv.notify_all();
            }
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(std::function<void()> printFizzBuzz) {
        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5 == 0) {
                std::unique_lock lk(mut);
                cv.wait(lk, [this, i] { return this->count == i; });
                printFizzBuzz();
                count++;
                lk.unlock();
                cv.notify_all();
            }
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(std::function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            if (i % 3 != 0 && i % 5 != 0) {
                std::unique_lock lk(mut);
                cv.wait(lk, [this, i] { return this->count == i; });
                printNumber(i);
                count++;
                lk.unlock();
                cv.notify_all();
            }
        }
    }
};