#include <vector>

class Solution {
  public:
    int numIslands(std::vector<std::vector<char>> &grid) {
        int m = grid.size(), n = grid[0].size(), islandCount = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != '1')
                    continue;
                islandCount++;
                dfsIsland(grid, i, j, m, n);
            }
        }

        return islandCount;
    }

  private:
    void dfsIsland(std::vector<std::vector<char>> &grid, int r, int c, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != '1')
            return;
        grid[r][c] = '2';
        dfsIsland(grid, r + 1, c, m, n);
        dfsIsland(grid, r - 1, c, m, n);
        dfsIsland(grid, r, c + 1, m, n);
        dfsIsland(grid, r, c - 1, m, n);
    }
};

// Calling a function 10,000 times sequentially is trivial for a 4GHz processor.
// Traversing dynamic container buffers 10,000 times is bottlenecked by main memory speed.

// for scan every tile
// if tile not visited yet -> bfs

// bfs: expand to all 1s -> same island