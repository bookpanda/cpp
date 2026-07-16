#include <functional>
#include <semaphore>

class H2O {
  private:
    std::counting_semaphore<2> hSem{2};
    std::binary_semaphore oSem{1};

  public:
    H2O() {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        hSem.acquire();
        releaseHydrogen();

        if (hSem.try_acquire()) {
            hSem.release();
        } else {
            oSem.release();
        }
    }

    void oxygen(std::function<void()> releaseOxygen) {
        oSem.acquire();
        releaseOxygen();
        hSem.release(2);
    }
};