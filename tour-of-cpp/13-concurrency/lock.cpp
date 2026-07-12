#include <mutex>

std::mutex m, m1, m2; // controlling mutex
int sh;               // shared data

void f() {
    std::unique_lock<std::mutex> lck{m}; // acquire mutex
    sh += 7;                             // manipulate shared data
} // release mutex implicitly

void f_simultanous() {
    std::unique_lock<std::mutex> lck1{m1, std::defer_lock};
    std::unique_lock<std::mutex> lck2{m2, std::defer_lock};
    //...
    std::lock(lck1, lck2);
} // implicitly release mutexes

int main(void) {
    f();
    return 0;
}