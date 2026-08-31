#include <algorithm>
#include <vector>

class Solution {
  public:
    int lengthOfLIS(std::vector<int> &nums) {
        int n = nums.size();
        std::vector<int> ans;
        ans.push_back(nums[0]);

        for (int i = 1; i < n; i++) {
            if (nums[i] > ans.back()) {
                ans.push_back(nums[i]);
                continue;
            }

            auto it = std::lower_bound(ans.begin(), ans.end(), nums[i]);
            *it = nums[i];
        }

        return ans.size();
    }
};

// [10,9,2,5,3,7,101,18]
// i=0: [10], len = LIS len
// i=1, [9]
// i=2, [2]
// i=3, [2,5]
// i=4, [2,3]
// i=5, [2,3,7]
// i=6, [2,3,7,101]
// i=7, [2,3,7,18]
// dp[i] = LIS of nums[0..i] && the LIS ends w/ nums[i]
// dp[i] = if(num[i] > nums[j]): take max dp[j]