#include <algorithm>
#include <vector>

class Solution {
  public:
    int maxProfit(std::vector<int> &prices) {
        int pastMaxProfit = 0;
        int n = prices.size();
        std::vector<int> sell(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int profit = prices[j] - prices[i];
                sell[j] = std::max(sell[j], profit + pastMaxProfit);
            }
            if (i > 0)
                pastMaxProfit = std::max(pastMaxProfit, sell[i - 1]);
        }
        pastMaxProfit = std::max(pastMaxProfit, sell[n - 1]);

        return pastMaxProfit;
    }
};
// dp[i] = max profit at day i
// dp[i][0] = state of holding stock
// dp[i][1] = state of not holding stock
// dp[i][0] = max(dp[i-1][0], dp[i-1][1])
// dp[i][1] = max(dp[i-1][1], dp[i-1][0] + )