#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

class Solution {
  public:
    int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k) {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);

        std::vector<std::vector<std::pair<int, int>>> adjList(n + 1);
        for (const auto &time : times) {
            // adjList[time[0]].push_back({time[1], time[2]});
            // constructs the std::pair in place within the queue rather than creating a temporary object and
            // copying/moving it.
            adjList[time[0]].emplace_back(time[1], time[2]);
        }

        std::vector<int> shortestPath(n + 1, INT_MAX);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>
            pq;
        pq.push({0, k});
        shortestPath[k] = 0;

        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();

            if (dist > shortestPath[u])
                continue;

            for (const auto &[v, w] : adjList[u]) {
                if (dist + w < shortestPath[v]) {
                    shortestPath[v] = dist + w;
                    pq.emplace(dist + w, v);
                }
            }
        }

        int maxPath = 0;
        for (int i = 1; i <= n; i++) {
            // cout << "shortestPath[" << i << "]=" << shortestPath[i] << "\n";
            if (shortestPath[i] == INT_MAX)
                return -1;
            maxPath = std::max(maxPath, shortestPath[i]);
        }

        return maxPath;
    }
};
// times(edges) -> convert to adjList
// dijstra algo starting from k: pq({dist, k}) sorted by dist asc

// times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// 2->1
// 2->3->4