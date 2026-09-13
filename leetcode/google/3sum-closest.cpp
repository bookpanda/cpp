#include <algorithm>
#include <climits>
#include <cstdlib>
#include <vector>

class Solution {
  public:
    int threeSumClosest(std::vector<int> &nums, int target) {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int ans = 0, minDiff = INT_MAX;

        for (int i = 0; i < n; i++) {
            int j = i + 1, k = n - 1;
            while (j < n && k >= 0 && j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                int diff = std::abs(sum - target);
                if (minDiff > diff) {
                    minDiff = diff;
                    ans = sum;
                }

                if (sum > target) {
                    k--;
                } else {
                    j++;
                }
            }
        }

        return ans;
    }
};

// [-4,-1,1,2]
// for i
// j=i+1, k=n-1

// sum3: sum > target: k--
// sum <target: j++
// closest = little less than or little more than or exact
// - want both sum that undershoot and overshoot target

// 1,1,2,10, t=5