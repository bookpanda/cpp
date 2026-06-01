#include <algorithm>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    int longestConsecutive(std::vector<int> &nums) {
        std::unordered_set<int> set;
        set.reserve(nums.size());
        for (int num : nums) {
            set.insert(num);
        }

        int lcs = 0;
        for (int num : set) {
            // if it's not the true start of sequence, don't do it
            if (set.find(num - 1) != set.end())
                continue;

            int currentNum = num;
            int streak = 1;

            while (set.find(currentNum + 1) != set.end()) {
                currentNum++;
                streak++;
            }
            lcs = std::max(lcs, streak);
            // cout << "lcs from " << num << " = " << size << "\n";
        }

        return lcs;
    }
};

// [9, 8, 7, 6,5,4,3,2,1]
// [100,4,200,1,3,2] put in unordered_set s
// loop member m: ask if s has m+1, ask if s has m+2...