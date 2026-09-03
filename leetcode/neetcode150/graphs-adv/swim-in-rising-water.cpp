#include <vector>

class Solution {
  private:
    int n;
    static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool dfs(std::vector<std::vector<int>> &grid, std::vector<std::vector<bool>> &visited, int r, int c, int lvl) {
        if (r == n - 1 && c == n - 1)
            return true;
        visited[r][c] = true;
        int res = false;

        int orig = grid[r][c];
        for (int i = 0; i < 4; i++) {
            int nr = r + dirs[i][0];
            int nc = c + dirs[i][1];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[nr][nc] || grid[nr][nc] > lvl)
                continue;

            res |= dfs(grid, visited, nr, nc, lvl);
            if (res)
                break;
        }

        return res;
    }

  public:
    int swimInWater(std::vector<std::vector<int>> &grid) {
        n = grid.size();
        int high = n * n - 1;
        int low = grid[0][0];
        int ans = high;

        while (low <= high) {
            int mid = (high + low) / 2;

            std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
            bool res = dfs(grid, visited, 0, 0, mid);
            if (res) {
                ans = std::min(ans, mid);
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};