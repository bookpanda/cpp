#include <functional>
#include <semaphore>

class ZeroEvenOdd {
  private:
    int n;
    std::binary_semaphore zeroSem{1};
    std::binary_semaphore oddSem{0};
    std::binary_semaphore evenSem{0};

  public:
    ZeroEvenOdd(int n) { this->n = n; }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber) {
        for (int i = 0; i < n; i++) {
            zeroSem.acquire();
            printNumber(0);
            if (i & 1)
                evenSem.release();
            else
                oddSem.release();
        }
    }

    void even(std::function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            evenSem.acquire();
            printNumber(i);
            zeroSem.release();
        }
    }

    void odd(std::function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            oddSem.acquire();
            printNumber(i);
            zeroSem.release();
        }
    }
};