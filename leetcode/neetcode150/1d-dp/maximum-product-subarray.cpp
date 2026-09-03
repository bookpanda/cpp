#include <vector>

class Solution {
  public:
    int maxProduct(std::vector<int> &nums) {
        int recentMin = nums[0];
        int recentMax = nums[0];
        int ans = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < 0) {
                std::swap(recentMin, recentMax);
            }

            recentMin = std::min(nums[i], recentMin * nums[i]);
            recentMax = std::max(nums[i], recentMax * nums[i]);
            ans = std::max(ans, recentMax);
        }
        return ans;
    }
};

// - < 0 < +
// suppose we have existing product from nums[a..b]
// see nums[b+1]: -, 0, +
// dp[i] = max product in nums[0..i] = dp[b+1] = max(dp[b] (dont take dp[b+1]), nums[b+1],)
// dp[i][0]= dont take nums[i] = max(dp[i-1][1], dp[i-1][0])
// dp[i][1]= take nums[i] = max(dp[i-1][1]*nums[i], nums[i])

// 2,3,-2,4
// dp[0][0] = INT_MIN,  dp[0][1] = nums[0] = 2
// dp[1][0] = 2,        dp[1][1] = 6
// dp[2][0] = 6,        dp[2][1] = -2
// dp[3][0] = 6,        dp[3][1] = 4

// [-2,3,-4]
// dp[0][0] = INT_MIN,  dp[0][1] = nums[0] = -2
// dp[1][0] = -2,       dp[1][1] = 3
// dp[2][0] = 3,        dp[2][1] = 0

// nums:
// if nums has 0: only ans 0 if all the rest are <0
// if