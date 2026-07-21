#include <algorithm>
#include <execution>
#include <mutex>
#include <vector>

class X {
    mutable std::mutex m;
    int data;

  public:
    X() : data(0) {}
    int get_value() const {
        std::lock_guard guard(m);
        return data;
    }
    void increment() {
        std::lock_guard guard(m);
        ++data;
    }
};
// can't use par_unseq because of the internal synchronization of the mutex
void increment_all(std::vector<X> &v) {
    std::for_each(std::execution::par, v.begin(), v.end(), [](X &x) { x.increment(); });
}