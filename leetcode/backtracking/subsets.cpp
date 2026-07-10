#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        std::vector<std::vector<int>> powerSet;
        std::vector<int> v;
        getPowerSet(nums, 0, v, powerSet);

        return powerSet;
    }
    void getPowerSet(std::vector<int> &nums, int idx, std::vector<int> &v, std::vector<std::vector<int>> &powerSet) {
        if (idx == nums.size()) {
            powerSet.push_back(v);
            return;
        }

        // take
        v.push_back(nums[idx]);
        getPowerSet(nums, idx + 1, v, powerSet);

        // not take
        v.pop_back();
        getPowerSet(nums, idx + 1, v, powerSet);
    }
};
// [1,2,3]
// [1] or []
// [2] or []
// [3] or []

// [0]
// [[0], []]