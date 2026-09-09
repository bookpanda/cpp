#include <algorithm>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals) {
        std::sort(intervals.begin(), intervals.end());
        std::vector<std::vector<int>> result;
        int prevEnd = -1;
        for (const auto &interval : intervals) {
            if (prevEnd >= interval[0]) {
                // merge
                result.back()[1] = std::max(result.back()[1], interval[1]);
            } else { // non-overlapping
                result.push_back(interval);
            }
            prevEnd = result.back()[1];
        }

        return result;
    }
};