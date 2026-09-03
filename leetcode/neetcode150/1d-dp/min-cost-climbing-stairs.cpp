#include <vector>

class Solution {
  public:
    int minCostClimbingStairs(std::vector<int> &cost) {
        std::vector<int> dp(cost.size() + 1, 0);
        for (int i = 2; i <= cost.size(); i++) {
            dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }

        return dp[cost.size()];
    }
};
// cost[i]
// cost = [10,15,20], top is 1 lvl beyond last cost (idx 3)
// dp[i] = cheapest cost to get to step i
// dp[0] = dp[1] = 0
// dp[i] = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2])
// dp[2] = min(0+15, 0+10) = 10
// dp[3] = min(dp[2]+cost[2], dp[1]+cost[1]) = min(10+20, 0+15) = 15

//.        0. 1. 2.3 4  5. 6 7  8  9
// cost = [1,100,1,1,1,100,1,1,100,1]
// dp[0] = dp[1] = 0
// dp[2] = 1
// dp[3] = 2, dp[4]=2, dp[5]=3, dp[6]=3, dp[7]=4, dp[8]=4, dp[9]=5, dp[10]=6