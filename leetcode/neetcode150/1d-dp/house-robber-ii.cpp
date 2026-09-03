#include <algorithm>
#include <vector>

class Solution {
  private:
    int robLinear(std::vector<int> &nums, int stIdx, int edIdx) {
        int prev2 = 0;
        int prev1 = 0;
        int curr;
        for (int i = stIdx; i <= edIdx; i++) {
            curr = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }

        return curr;
    }

  public:
    int rob(std::vector<int> &nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        // 1. rob nums[0..n-2]
        // 2. rob nums[1..n-1]
        return std::max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }
};
// nums = [1, 2, 3, 1] = 4
// dp[0][0]=1, dp[0][1]=0
// dp[1][0]=2, dp[1][1]=2
// dp[2][0]=4, dp[2][1]=3
// dp[3][0]=, dp[3][1]=3

// nums = [2, 3, 2] = 3
// dp[0][0]=2, dp[0][1]=0
// dp[1][0]=3, dp[1][1]=3
// dp[2][0]=4, dp[2][1]=3

// dp[i] = max sum from nums[0...i]
// 1. rob first house = can't rob last house: dp[i][0]
// 2. don't rob first house = can rob last house: dp[i][1]
// return max(dp[n-2][0], dp[n-1][1])