#include <vector>

class Solution {
  public:
    int climbStairs(int n) {
        std::vector<int> dp(n + 1, 0);
        // dp[i] = # of distinct ways to get to ith step
        dp[0] = 1;
        dp[1] = 1; // 0->1

        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
            // ith step can be either from i-1th step + 1, or i-2th step + 2
        }

        return dp[n];
    }
};