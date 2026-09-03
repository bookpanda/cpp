#include <algorithm>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
        if (nums.size() < 3)
            return {};

        std::sort(nums.begin(), nums.end());
        size_t n = nums.size();

        std::vector<std::vector<int>> ans;

        for (size_t i = 0; i < n - 2; i++) {
            if (nums[i] > 0)
                break;
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            size_t j = i + 1;
            size_t k = n - 1;
            // i < j < k -> nums[i] <= nums[j] <= nums[k]

            while (j < k) {
                long long sum = static_cast<long long>(nums[i]) + nums[j] + nums[k];
                if (sum > 0) {
                    while (j < k && nums[k] == nums[k - 1])
                        k--;
                    k--;
                } else if (sum < 0) {
                    while (j < k && nums[j] == nums[j + 1])
                        j++;
                    j++;
                } else { // sum == 0
                    ans.push_back({nums[i], nums[j], nums[k]});
                    while (j < k && nums[j] == nums[j + 1])
                        j++;
                    j++;
                    while (j < k && nums[k] == nums[k - 1])
                        k--;
                    k--;
                }
            }
        }
        // [-1,0,1,2,-1,-4] -> [-4, -1, -1, 0, 1, 2]
        // i=3, j=4,k=5
        // ans: {-1,-1,2}, {-1, 0, 1}
        // [3, 3, -1, -1, 5, -1, -1, -2, -2, -2]
        //. i.     j->              <-k

        return ans;
    }
};

// naive: 3 for loops (3000^3) too slow

// sort it first O(nlogn)
// for i , search for (j,k) between [i+1, n)
// O(n)         num[i] +num[j]+num[k] > 0 : k--
//  num[i] +num[j]+num[k] < 0 : j++ O(n)

// O(n^2)