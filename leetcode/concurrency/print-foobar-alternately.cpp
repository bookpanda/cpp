#include <functional>
#include <semaphore>

class FooBar {
  private:
    int n;
    std::binary_semaphore semFoo{1};
    std::binary_semaphore semBar{0};

  public:
    FooBar(int n) { this->n = n; }

    void foo(std::function<void()> printFoo) {

        for (int i = 0; i < n; i++) {
            semFoo.acquire();
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            semBar.release();
        }
    }

    void bar(std::function<void()> printBar) {

        for (int i = 0; i < n; i++) {
            semBar.acquire();
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            semFoo.release();
        }
    }
};