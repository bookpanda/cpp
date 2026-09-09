#include <algorithm>
#include <queue>
#include <vector>

class Solution {
  public:
    int minMeetingRooms(std::vector<std::vector<int>> &intervals) {
        std::sort(intervals.begin(), intervals.end());
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        int maxRooms = 0;
        for (size_t i = 0; i < intervals.size(); i++) {
            // clear finished meetings
            while (!pq.empty() && pq.top() <= intervals[i][0]) {
                pq.pop();
            }
            pq.push(intervals[i][1]);
            maxRooms = std::max(maxRooms, static_cast<int>(pq.size()));
        }

        return maxRooms;
    }
};
// intervals = [[0,30], [0,20],[5,10],[15,20],]
// pq.push(-end)
// [0,30] => pq: {-30}
// [0,20] => pq: {-20,-30}
// [5,10] => pq: {-10,-20,-30}
// [15,20] => pq: {-20,-20,-30}

// overlap = need more concurrent rooms
// return the max no. of concurrent meetings
// 2 intervals overlap = 2 concurrent meetings

// check overlapping: sort by start
// prevEnd > currStart