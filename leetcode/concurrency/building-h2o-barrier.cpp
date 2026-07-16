#include <barrier>
#include <functional>
#include <semaphore>

class H2O {
  private:
    std::counting_semaphore<2> hSem{2};
    std::binary_semaphore oSem{1};
    std::barrier<> sync;

  public:
    H2O() : sync(3) {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        hSem.acquire();
        sync.arrive_and_wait();

        releaseHydrogen();
        hSem.release();
    }

    void oxygen(std::function<void()> releaseOxygen) {
        oSem.acquire();
        sync.arrive_and_wait();

        releaseOxygen();
        oSem.release();
    }
};