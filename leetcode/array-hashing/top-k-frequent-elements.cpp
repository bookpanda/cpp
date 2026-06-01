#include <unordered_map>
#include <vector>

class Solution {
  public:
    std::vector<int> topKFrequent(const std::vector<int> &nums, int k) {
        std::unordered_map<int, int> num2freq;
        num2freq.reserve(nums.size());
        for (int num : nums) {
            num2freq[num]++;
        }

        // direct O(1) array indexing and perfect cache locality
        std::vector<std::vector<int>> freq2nums(nums.size() + 1);
        for (const auto &[num, freq] : num2freq) {
            freq2nums[freq].push_back(num);
        }
        // freq2nums = 1:{3}, 2:{2}, 3:{1}
        // num2freq = 1:3, 2:2, 3:1

        std::vector<int> ans;
        for (size_t i = nums.size(); i > 0; i--) {
            for (int num : freq2nums[i]) {
                ans.push_back(num);
                if (ans.size() == k)
                    return ans;
            }
        }
        return ans;
    }
};

// [1,1,1,2,2,3]
// freq2nums[freq >= 0] = map of numbers w/ freq = freq
// count[ferq] = vector<int>