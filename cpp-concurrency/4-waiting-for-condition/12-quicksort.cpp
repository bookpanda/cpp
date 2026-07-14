#include <list>

template <typename T> std::list<T> sequential_quick_sort(std::list<T> input) {
    if (input.empty()) {
        return input;
    }

    std::list<T> result;
    // move the first element of input to the beginning of result
    result.splice(result.begin(), input, input.begin());

    T const &pivot = *result.begin();
    // rearrange input so that elements < pivot are in the front, and elements >= pivot are in the back
    // divide_point points to 1st element >= pivot
    auto divide_point = std::partition(input.begin(), input.end(), [&](T const &t) { return t < pivot; });

    std::list<T> lower_part;
    // move the elements < pivot to the end of lower_part
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    auto new_lower(sequential_quick_sort(std::move(lower_part)));
    auto new_higher(sequential_quick_sort(std::move(input)));
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower);

    return result;
}