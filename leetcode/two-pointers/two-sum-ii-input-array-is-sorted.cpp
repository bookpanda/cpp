#include <cstdlib>
#include <vector>

class Solution {
  public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target) {
        size_t left = 0;
        size_t right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum > target) {
                right--;
            } else if (sum < target) {
                left++;
            } else {
                return {static_cast<int>(left) + 1, static_cast<int>(right) + 1};
            }
        }
        std::abort();
        return {};
    }
};