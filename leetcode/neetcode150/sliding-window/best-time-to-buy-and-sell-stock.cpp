#include <vector>

class Solution {
  public:
    int maxProfit(std::vector<int> &prices) {
        size_t buyDate = 0;
        int maxProfit = 0;

        for (size_t i = 1; i < prices.size(); i++) {
            int profit = prices[i] - prices[buyDate];
            maxProfit = std::max(maxProfit, profit);
            if (prices[i] < prices[buyDate]) {
                buyDate = i;
            }
        }
        // [7,1,5,3,6,4]
        //.   b       i
        // maxProfit 5

        return maxProfit;
    }
};

// [7,1,5,3,6, 0,4]
//             b s
// buy date: always stick to observed lowest prices
// loop i: profit = prices[i] - buyPrice
//

// keep maxProfit = max(maxProfit, profit)
// if price drops -> new buy date
// if price rises -> new sell date?