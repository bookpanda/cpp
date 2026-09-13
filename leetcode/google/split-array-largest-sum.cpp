#include <algorithm>
#include <vector>

class Solution {
  public:
    int splitArray(std::vector<int> &nums, int k) {
        int maxNum = 0;
        int high = 0, low = 0, n = nums.size();
        for (int num : nums) {
            maxNum = std::max(maxNum, num);
            high += num;
        }

        while (low <= high) {
            int mid = (high + low) / 2;
            if (mid < maxNum) {
                low = mid + 1;
                continue;
            }

            // sum <= mid
            int sum = 0, used = 1;
            for (int i = 0; i < n; i++) {
                if (sum + nums[i] > mid) {
                    used++;
                    sum = nums[i];
                } else {
                    sum += nums[i];
                }
            }
            // cout << "h"<<high<<", l"<<low<< ",mid = " << mid << ", largestSum="<<largestSum << ", used=" << used <<
            // "\n";
            if (used <= k) { // mid is large enough, try smaller
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};

// nums = [7,2,5,10,8], k = 2

// 1000, split into 50 contiguous parts
// dp[j+1][k] = max sum(any part in nums[0..j] split into k parts)
// dp[0][0] = 0
// dp[1][0] = nums[0]

// int dc(idx, k) {
// idx == n: return 0
// dp[idx][k] = max sum of any subarry in nums[0..idx] split into k parts
// return max of 2 choices:
// 1. add nums[idx] to current subarray sum
// max(nums[idx]+sum, dc(idx+1, k))
// 2. cut (k+1), new subarray sum = nums[idx];
// max(sum, dc(idx+1,k+1))
// }
// [1000][1000][50]