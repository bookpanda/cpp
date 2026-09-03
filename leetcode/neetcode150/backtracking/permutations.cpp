#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> permutations;
    std::vector<std::vector<int>> permute(std::vector<int> &nums) {
        // std::vector<bool> used(nums.size());
        int used = 0;
        std::vector<int> permu;
        getPermutations(nums, permu, used);

        return permutations;
    }
    void getPermutations(std::vector<int> &nums, std::vector<int> &permu, int &used) {
        if (permu.size() == nums.size()) {
            permutations.push_back(permu);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used & (1 << i))
                continue;

            used |= 1 << i;
            permu.push_back(nums[i]);
            getPermutations(nums, permu, used);
            used ^= 1 << i;
            permu.pop_back();
        }
    }
};
// n distinct items -> n! ways
// [1,2,3]

// f([], 0) -> f([1], 1), f([2], 1), f([3], 1)
// f([1], 1) -> f([1,2], 2), f([1,3], 2)
// f([2], 1) -> f([2,1], 2), f([2,3], 2)
// f([3], 1) -> f([3,1], 2), f([3,2], 2)
// f([1,2,3], 3), f([1,3, 2], 2)