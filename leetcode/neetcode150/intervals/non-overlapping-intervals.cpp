#include <algorithm>
#include <vector>

class Solution {
  public:
    int eraseOverlapIntervals(std::vector<std::vector<int>> &intervals) {
        auto comp = [](const std::vector<int> &a, const std::vector<int> &b) { return a[1] < b[1]; };
        std::sort(intervals.begin(), intervals.end(), comp);

        int prevEnd = intervals[0][1];
        int count = 0;
        for (size_t i = 1; i < intervals.size(); i++) {
            if (prevEnd > intervals[i][0]) {
                // overlap
                // prevEnd = std::min(prevEnd, interval[1]);
                count++;
            } else {
                // no overlap (interval[0] > prevEnd => interval[1] >= interval[0])
                prevEnd = intervals[i][1];
            }
        }

        return count;
    }
};

// intervals = [[1,2],[1,3],[2,3],[3,4]]
// [1,2], prevEnd=2
// [1,3], prevEnd=2, c=1
// [2,3],
// intervals = [[1,2],[1,2],[1,2]]
// intervals = [[1,2],[2,3]]

// problems where goal is to merge intevals
// sort by start, prevEnd > currStart: merge

// prev (), curr [], next {}
// ( [ ) { ] }
// prevEnd > currStart && currEnd > nextStart
// if curr overlaps w/ prev, should remove the interval that has higher end so the minimize chance that the one not
// removed doesnt overlap w/ next intervals