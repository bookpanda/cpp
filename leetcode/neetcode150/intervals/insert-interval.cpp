#include <algorithm>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals, std::vector<int> &newInterval) {
        std::vector<std::vector<int>> result;

        auto it = std::lower_bound(intervals.begin(), intervals.end(), newInterval);
        intervals.insert(it, newInterval);
        // intervals.push_back(newInterval);
        // sort(intervals.begin(), intervals.end());

        // std::vector<int> prev = {-1, -1};
        int prevEnd = -1;
        for (const auto &interval : intervals) {
            // if (prev[1] >= interval[0] && interval[1] >= prev[0]) { // overlap
            if (prevEnd >= interval[0]) {
                // merge
                result.back()[1] = std::max(result.back()[1], interval[1]);
            } else { // no overlap: push
                // if (prev[0] != -1) result.push_back(prev);
                // prev = interval;
                result.push_back(interval);
            }
            prevEnd = result.back()[1];
        }
        // if (prev[0] != -1) result.push_back(prev);

        return result;
    }
};
// A=(), B={}
// () {} : A.end < B.start || B.end < A.start
// ( { ) } : A.end > B.start && B.end > A.start = { ) }
// or  B.end > A.start && A.end > B.start = ( } )