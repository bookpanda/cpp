#include <cmath>
#include <numeric>
#include <vector>

class Solution {
  public:
    int findTargetSumWays(std::vector<int> &nums, int target) {
        // P = set of numbers w/ +
        // N = set of numbers w/ -
        // sum(P) - sum(N) = target
        // sum(P) + sum(N) = sum(nums)
        // add 2 equa: sum(P) = (target + sum(nums)) / 2
        // reframe problem: find no. ways to pick some numbers from nums s.t. sum is sum(P)
        // the unpicked numbers naturally sums up to sum(N)

        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (std::abs(target) > sum || (target + sum) % 2 != 0)
            return 0;

        int sumP = (target + sum) / 2;
        std::vector<int> dp(sumP + 1, 0);
        dp[0] = 1;
        for (int num : nums) {
            for (int i = sumP; i >= num; i--) {
                dp[i] += dp[i - num];
            }
        }
        return dp[sumP];
    }
};