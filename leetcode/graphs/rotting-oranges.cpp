#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

class Solution {
  public:
    int orangesRotting(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size(), freshOranges = 0, maxTime = 0;
        std::queue<std::tuple<int, int, int>> q;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1)
                    freshOranges++;
                else if (grid[i][j] == 2)
                    q.push({i, j, 0});
            }
        }

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        while (!q.empty()) {
            auto [r, c, t] = q.front();
            q.pop();
            maxTime = std::max(maxTime, t);

            for (int i = 0; i < 4; i++) {
                int newR = r + dr[i];
                int newC = c + dc[i];
                if (newR < 0 || newR >= m || newC < 0 || newC >= n || grid[newR][newC] != 1)
                    continue;
                q.push({newR, newC, t + 1});
                grid[newR][newC] = 3;
                freshOranges--;
            }
        }

        if (freshOranges > 0)
            return -1;
        return maxTime;
    }
};

// for each cell: record all rotting oranges
// -> bfs starting from roting oragnges -> spread until queue is empty
// is queue empty but fresh ornage count > 0 -> return -1
// else return latest timestamp in queue