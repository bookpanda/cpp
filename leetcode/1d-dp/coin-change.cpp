#include <algorithm>
#include <vector>

class Solution {
  public:
    int coinChange(std::vector<int> &coins, int amount) {
        if (amount == 0)
            return 0;
        const int INF = amount + 1;
        std::vector<int> knap(amount + 1, INF);
        knap[0] = 0;

        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                knap[i] = std::min(knap[i], knap[i - coin] + 1);
            }
        }

        return knap[amount] == INF ? -1 : knap[amount];
    }
};
// i=INT_MAX
//.     0,1,2,3,4,5,6,7,8,9
// knap[0,i,i,i,i,i,i,i,i,i]
// coin 1
// knap[0,1,2,3,4,5,6,7,8,9]
// coin 2: knap[i] = min(knap[i], knap[i-2]+1)
// knap[0,1,1,2,2,3,3,4,4,5]
// coin 5: knap[i] = min(knap[i], knap[i-5]+1)
// knap[0,1,1,2,2,1,2,2,3,3]