#include <algorithm>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>

// THIS CODE IS NOT EXCEPTION SAFE
template <typename Iterator, typename T> struct accumulate_block {
    void operator()(Iterator first, Iterator last, T &result) {
        // can throw
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T> T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    if (!length)
        return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;

    // allocation can throw, but haven't done any work or spawned any threads, so ok
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    Iterator block_start = first;

    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        // if new thread throws any exceptions, program will terminate (BAD)
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }

    // last block of work is done by the main thread
    // can throw
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    // can throw, but since all threads have been joined, it'll throw w/o causing problems
    return std::accumulate(results.begin(), results.end(), init);
}