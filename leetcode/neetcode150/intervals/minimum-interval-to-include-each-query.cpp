#include <algorithm>
#include <queue>
#include <vector>

class Solution {
  public:
    std::vector<int> minInterval(std::vector<std::vector<int>> &intervals, std::vector<int> &queries) {
        int n = intervals.size(), q = queries.size();
        std::sort(intervals.begin(), intervals.end());

        std::vector<std::pair<int, int>> sortedQueries(q);
        for (int i = 0; i < q; i++) {
            sortedQueries[i] = {queries[i], i};
        }
        std::sort(sortedQueries.begin(), sortedQueries.end());

        using P = std::pair<int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> minHeap;

        int i = 0;
        std::vector<int> ans(q, -1);
        for (const auto &[query, idx] : sortedQueries) {
            while (i < n && intervals[i][0] <= query) {
                // getting intervals that start <= query
                int size = intervals[i][1] - intervals[i][0] + 1;
                minHeap.push({size, intervals[i][1]});
                i++;
            }
            // remove the top intervals w/ end < query
            while (!minHeap.empty() && minHeap.top().second < query) {
                minHeap.pop();
            }

            if (!minHeap.empty())
                ans[idx] = minHeap.top().first;
        }

        return ans;
    }
};