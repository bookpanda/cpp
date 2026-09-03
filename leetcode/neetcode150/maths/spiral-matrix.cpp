#include <climits>
#include <vector>

class Solution {
  public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix) {
        int r = 0, c = 0;
        const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int turn = 0;
        std::vector<int> ans;

        int m = matrix.size(), n = matrix[0].size();
        while (ans.size() < m * n) {
            int nr = r + dirs[turn][0];
            int nc = c + dirs[turn][1];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n || matrix[nr][nc] == INT_MAX) {
                turn = (turn + 1) % 4;
                // cout << "turn " << turn << "\n";
                nr = r + dirs[turn][0];
                nc = c + dirs[turn][1];
                // continue;
            }
            // cout << "push " << matrix[r][c] << "\n";
            ans.push_back(matrix[r][c]);
            matrix[r][c] = INT_MAX;
            r = nr;
            c = nc;
        }
        return ans;
    }
};