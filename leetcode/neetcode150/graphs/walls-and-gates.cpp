#include <climits>
#include <queue>
#include <vector>

class Solution {
  public:
    void wallsAndGates(std::vector<std::vector<int>> &rooms) {
        int m = rooms.size(), n = rooms[0].size();
        std::queue<std::pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    q.push({i, j});
                    rooms[i][j] = 0;
                }
            }
        }

        constexpr int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + dirs[i][0];
                int nc = c + dirs[i][1];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n || rooms[nr][nc] != INT_MAX)
                    continue;
                q.push({nr, nc});
                rooms[nr][nc] = rooms[r][c] + 1;
            }
        }
    }
};