#include <array>
#include <functional>
#include <semaphore>

class DiningPhilosophers {
  private:
    // std::vector<std::binary_semaphore> forks;
    std::array<std::binary_semaphore, 5> forks{std::binary_semaphore{1}, std::binary_semaphore{1},
                                               std::binary_semaphore{1}, std::binary_semaphore{1},
                                               std::binary_semaphore{1}};

  public:
    DiningPhilosophers() {
        // for (int i=0;i<5;i++) {
        //     forks.push_back(new std::binary_semaphore());
        // }
    }

    // forks[pid], forks[(pid+1)%5]
    void wantsToEat(int pid, std::function<void()> pickLeftFork, std::function<void()> pickRightFork,
                    std::function<void()> eat, std::function<void()> putLeftFork, std::function<void()> putRightFork) {
        int right = pid;
        int left = (pid + 1) % 5;

        // Break symmetry: The last philosopher picks up right then left.
        // Everyone else picks up left then right.
        if (pid == 4) {
            forks[right].acquire();
            pickRightFork();
            forks[left].acquire();
            pickLeftFork();
        } else {
            forks[left].acquire();
            pickLeftFork();
            forks[right].acquire();
            pickRightFork();
        }

        eat();

        if (pid == 4) {
            putRightFork();
            forks[right].release();
            putLeftFork();
            forks[left].release();
        } else {
            putLeftFork();
            forks[left].release();
            putRightFork();
            forks[right].release();
        }
    }
};