#include <atomic>
#include <cstddef>
#include <future>
#include <iterator>

template <typename Iterator, typename MatchType>
Iterator parallel_find_impl(Iterator first, Iterator last, MatchType match, std::atomic<bool> &done) {
    try {
        unsigned long const length = std::distance(first, last);
        unsigned long const min_per_thread = 25;
        if (length < (2 * min_per_thread)) {
            for (; (first != last) && !done.load(); ++first) {
                if (*first == match) {
                    done = true;
                    return first;
                }
            }
            return last;
        } else {
            Iterator const mid_point = first + (length / 2);
            // [midpoint, last] is processed by async
            std::future<Iterator> async_result =
                std::async(&parallel_find_impl<Iterator, MatchType>, mid_point, last, match, std::ref(done));
            // [first, midpoint] is processed by this thread
            Iterator const direct_result = parallel_find_impl(first, mid_point, match, done);
            // if [first, midpoint] returns last, which is mid_point (no match), then wait for async result
            return (direct_result == mid_point) ? async_result.get() : direct_result;
            // 2 cases for async:
            // 1. async call is deferred, it will run then .get() is called, will be skipped if match found in
            // direct_result
            // 2. async call is running on separate thread, destructor will wait for it to complete, so no leaking
            // threads
        }
    } catch (...) {
        done = true;
        throw;
    }
}

template <typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match) {
    std::atomic<bool> done(false);
    return parallel_find_impl(first, last, match, done);
}