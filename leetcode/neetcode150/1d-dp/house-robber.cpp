#include <algorithm>
#include <vector>

class Solution {
  public:
    int rob(std::vector<int> &nums) {
        if (nums.size() == 1)
            return nums[0];

        std::vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = std::max(nums[i] + dp[i - 2], dp[i - 1]);
        }

        return dp[nums.size() - 1];
    }
};
// nums = [1,2,3,1]
// max sum in num s.t. selected idxes are NOT adjacent
// dp[i] = max value sum from nums[0..i]
// dp[0]=1, dp[1]=2
// dp[2]= max(nums[2]+dp[0], dp[1])=max(3+1, 2) = 4
// dp[3]=max(nums[3]+dp[1], dp[2])=max(1+2, 4)=4
// max(nums[i] + dp[i-2] take itself, dp[i-1] not take itself)

// nums = [2,7,9,3,1] = 12
// dp[0]=2, dp[1]=7
// dp[2] = max(9+2, 7) = 11
// dp[3] = max(3+7, 11) = 11
// dp[4] = max(1+11, 11) = 12