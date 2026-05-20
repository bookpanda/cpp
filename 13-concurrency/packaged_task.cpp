#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// simplify setting tasks connected w/ futures and promises
double accum(double *beg, double *end, double init)
// compute the sum of [beg:end) starting with the initial value init
{
    return std::accumulate(beg, end, init);
}

double comp2(std::vector<double> &v) {
    using Task_type = double(double *, double *, double); // type of task

    std::packaged_task<Task_type> pt0{accum};  // package the task (i.e., accum)
    std::future<double> f0 = pt0.get_future(); // get hold of pt0’s future

    std::packaged_task<Task_type> pt1{accum};  // package the task (i.e., accum)
    std::future<double> f1 = pt1.get_future(); // get hold of pt1’s future

    double *first = &v[0];
    std::thread t1{std::move(pt0), first, first + v.size() / 2, 0};            // start a thread for pt0
    std::thread t2{std::move(pt1), first + v.size() / 2, first + v.size(), 0}; // start a thread for pt1

    double result = f0.get() + f1.get(); // get the results
    t1.join();
    t2.join();
    return result;
}

double comp4(std::vector<double> &v) // spawn many tasks if v is large enough
{
    if (v.size() < 10000) // is it worth using concurrency?
        return std::accumulate(v.begin(), v.end(), 0.0);

    auto v0 = &v[0];
    auto sz = v.size();
    // std::async does not guarantee that a new thread will be spawned. Depending on how you call it, it might execute
    // your task synchronously on the current thread the moment you ask for the result, completely defeating the purpose
    // of parallelism.
    auto f0 = std::async(accum, v0, v0 + sz / 4,
                         0.0);                                      // first quarter
    auto f1 = std::async(accum, v0 + sz / 4, v0 + sz / 2, 0.0);     // second quarter
    auto f2 = std::async(accum, v0 + sz / 2, v0 + sz * 3 / 4, 0.0); // third quarter
    auto f3 = std::async(accum, v0 + sz * 3 / 4, v0 + sz, 0.0);     // fourth quarter
    return f0.get() + f1.get() + f2.get() + f3.get();               // collect and combine the results
}

int main() {
    std::vector<double> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double result = comp2(v);
    std::cout << "Result: " << result << std::endl;

    result = comp4(v);
    std::cout << "Result comp4: " << result << std::endl;
    return 0;
}