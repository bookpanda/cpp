#include <vector>

class Solution {
  public:
    std::vector<int> productExceptSelf(std::vector<int> &nums) {
        const size_t n = nums.size();
        std::vector<int> ans(n);
        ans[0] = 1;
        for (size_t i = 1; i < n; i++) {
            ans[i] = ans[i - 1] * nums[i - 1]; // prefix
        }
        int suffix = 1;
        for (size_t i = n; i > 0; i--) {
            size_t idx = i - 1;
            ans[idx] *= suffix;
            suffix *= nums[idx];
        }
        // [1,2,3,4]
        // prefix: [1, 1, 2, 6]
        // suffix: [24, 12, 8, 6], suf = 24

        return ans;
    }
};

// [-1,1,0,-3,3]
// prefix: [-1, -1, 0, 0, 0]
// suffix: [0, 0, 0, -9, 3]