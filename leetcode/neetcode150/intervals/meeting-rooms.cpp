#include <algorithm>
#include <vector>

class Solution {
  public:
    bool canAttendMeetings(std::vector<std::vector<int>> &intervals) {
        if (intervals.size() == 0)
            return true;

        std::sort(intervals.begin(), intervals.end());
        int prevEnd = intervals[0][1];

        for (size_t i = 1; i < intervals.size(); i++) {
            if (prevEnd > intervals[i][0])
                return false;
            else
                prevEnd = intervals[i][1];
        }

        return true;
    }
};