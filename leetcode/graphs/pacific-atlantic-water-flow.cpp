#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>> &heights) {
        int m = heights.size(), n = heights[0].size();
        std::vector<uint8_t> visited(m * n, 0);

        // pacific top
        for (int i = 0; i < n; i++) {
            dfs(heights, 0, i, m, n, visited, 1, 0);
        }
        // pacific left
        for (int i = 0; i < m; i++) {
            dfs(heights, i, 0, m, n, visited, 1, 0);
        }

        // atlantic right
        for (int i = 0; i < m; i++) {
            dfs(heights, i, n - 1, m, n, visited, 2, 0);
        }
        // atlantic bottom
        for (int i = 0; i < n; i++) {
            dfs(heights, m - 1, i, m, n, visited, 2, 0);
        }

        std::vector<std::vector<int>> tiles;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (visited[i * n + j] == 3)
                    tiles.push_back({i, j});
            }
        }

        return tiles;
    }

  private:
    void dfs(std::vector<std::vector<int>> &heights, int r, int c, int m, int n, std::vector<uint8_t> &visited, int ap,
             int prevHeight) {
        if (r < 0 || r >= m || c < 0 || c >= n || visited[r * n + c] & ap || prevHeight > heights[r][c])
            return;
        visited[r * n + c] |= ap;

        dfs(heights, r + 1, c, m, n, visited, ap, heights[r][c]);
        dfs(heights, r - 1, c, m, n, visited, ap, heights[r][c]);
        dfs(heights, r, c + 1, m, n, visited, ap, heights[r][c]);
        dfs(heights, r, c - 1, m, n, visited, ap, heights[r][c]);
    }
};
// 2 bfs
// 1. start from pacific edges, spread if height[next]>=height[curr]
// 2. start from atlantic edges, spread if height[next]>=height[curr]
// both bfs, keep track of final reached tiles
// intersect 2 maps together
