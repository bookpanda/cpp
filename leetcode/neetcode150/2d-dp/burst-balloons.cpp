#include <algorithm>
#include <vector>

class Solution {
  public:
    int maxCoins(std::vector<int> &nums) {
        int n = nums.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
        return dc(nums, 0, n - 1, dp);
    }

  private:
    int dc(std::vector<int> &nums, int l, int r, std::vector<std::vector<int>> &dp) {
        if (l > r)
            return 0;
        if (dp[l][r] != -1)
            return dp[l][r];
        if (l == r) {
            int lastToPop = nums[l];
            if (l - 1 >= 0)
                lastToPop *= nums[l - 1];
            if (r + 1 < nums.size())
                lastToPop *= nums[r + 1];
        }

        int maxCoin = 0;
        for (int k = l; k <= r; k++) {
            int lastToPop = nums[k];
            if (l - 1 >= 0)
                lastToPop *= nums[l - 1];
            if (r + 1 < nums.size())
                lastToPop *= nums[r + 1];
            int sum = dc(nums, l, k - 1, dp) + dc(nums, k + 1, r, dp) + lastToPop;
            maxCoin = std::max(maxCoin, sum);
        }

        dp[l][r] = maxCoin;
        return maxCoin;
    }
};

// [1,3,5]
// [(1),3,5] = dc(nums,i,k-1) + nums[i-1]*(1)*nums[j+1] + dc(nums,k+1,j)
// [1,(3),5]

// [1] = 1
// [3, 5] = pop smaller one first always = 3*5+5=20
