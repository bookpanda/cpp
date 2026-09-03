#include <cstdint>
#include <vector>

class Solution {
  public:
    int change(int amount, std::vector<int> &coins) {
        std::vector<uint64_t> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] = dp[i] + dp[i - coin];
            }
        }
        return static_cast<int>(dp[amount]);
    }
};
// amount=5, [1, 2, 5]
//  0 1 2 3 4 5
// [1,0,0,0,0,0]
// [1,1,1,1,1,1] : dp[i] += dp[i-1]
// [1,1,2,2,3,3] : dp[i] += dp[i-2], 5: 11111, 1112, 122
// [1,1,2,2,3,4] : dp[i] += dp[i-5], 5: 11111, 1112, 122, 5

// dp[i]
// dp[i] = no. of ways to create sum of i from the coins