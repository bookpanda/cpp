#include <algorithm>
#include <vector>

class Solution {
  public:
    int longestIncreasingPath(std::vector<std::vector<int>> &matrix) {
        m = matrix.size(), n = matrix[0].size();

        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        int maxDist = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxDist = std::max(maxDist, dfs(matrix, i, j, dp));
            }
        }

        return maxDist;
    }

  private:
    int m, n;
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int dfs(const std::vector<std::vector<int>> &matrix, int r, int c, std::vector<std::vector<int>> &dp) {
        if (dp[r][c] != 0)
            return dp[r][c];

        int maxLength = 1;
        for (const auto &dir : dirs) {
            int nr = r + dir[0];
            int nc = c + dir[1];

            if (nr < 0 || nr >= m || nc < 0 || nc >= n || matrix[nr][nc] <= matrix[r][c])
                continue;
            maxLength = std::max(maxLength, 1 + dfs(matrix, nr, nc, dp));
        }

        dp[r][c] = maxLength;
        return dp[r][c];
    }
};

// if we've travelled x blocks and currently on matrix[i][j],
// this is the only state that matters
// dp[i][j] = max of x when curently on matrix[i][j]
// we dont care about which dir we came from (up/down/top/bottom) since the next tile is strictly > matrix[i][j], and
// where we came from is strictly < matrix[i][j]

// loop each cell -> call dfs starting on that cell, keeping track of dp[i][j]