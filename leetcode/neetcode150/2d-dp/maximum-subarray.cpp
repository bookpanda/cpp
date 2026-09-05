#include <algorithm>
#include <vector>

class Solution {
  public:
    int maxSubArray(std::vector<int> &nums) {
        int total = 0;
        int ans = nums[0];
        for (int num : nums) {
            total += num;
            ans = std::max(ans, total);
            if (total < 0)
                total = 0;
        }
        return ans;
    }
};