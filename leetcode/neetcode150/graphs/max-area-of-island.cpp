#include <vector>

class Solution {
  public:
    int maxAreaOfIsland(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size(), maxIslandArea = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 1)
                    continue;
                maxIslandArea = std::max(maxIslandArea, findIslandArea(grid, i, j, m, n));
            }
        }

        return maxIslandArea;
    }

  private:
    int findIslandArea(std::vector<std::vector<int>> &grid, int r, int c, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != 1)
            return 0;

        grid[r][c] = 2;
        int sum = findIslandArea(grid, r + 1, c, m, n) + findIslandArea(grid, r - 1, c, m, n) +
                  findIslandArea(grid, r, c + 1, m, n) + findIslandArea(grid, r, c - 1, m, n);

        return 1 + sum;
    }
};

// scan all tiles, if it's 1, check DFS for island size