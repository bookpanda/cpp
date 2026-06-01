#include <cstdlib>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    std::vector<int> twoSum(const std::vector<int> &nums, int target) {
        // x = target - nums[i]
        // check if x is in nums && x's idx is not i
        // lookup[x] = vector of idxes (maybe can just override)
        std::unordered_map<int, int> val2idx;
        val2idx.reserve(nums.size());

        for (size_t i = 0; i < nums.size(); i++) {
            int want = target - nums[i];
            auto it = val2idx.find(want);
            if (it != val2idx.end()) {
                return {static_cast<int>(i), it->second};
            }
            val2idx[nums[i]] = static_cast<int>(i);
        }
        // val2idx = 2:0,
        std::abort(); // unreachable
    }
};