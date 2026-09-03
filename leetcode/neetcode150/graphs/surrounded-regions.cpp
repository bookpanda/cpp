#include <queue>
#include <tuple>
#include <vector>

class Solution {
  public:
    void solve(std::vector<std::vector<char>> &board) {
        int m = board.size(), n = board[0].size();
        std::queue<std::tuple<int, int>> q;

        for (int i = 0; i < n; i++) { // top
            if (board[0][i] == 'O') {
                board[0][i] = 'P';
                q.push({0, i});
            }
        }
        for (int i = 0; i < m; i++) { // left
            if (board[i][0] == 'O') {
                board[i][0] = 'P';
                q.push({i, 0});
            }
        }
        for (int i = 0; i < m; i++) { // right
            if (board[i][n - 1] == 'O') {
                board[i][n - 1] = 'P';
                q.push({i, n - 1});
            }
        }
        for (int i = 0; i < n; i++) { // bottom
            if (board[m - 1][i] == 'O') {
                board[m - 1][i] = 'P';
                q.push({m - 1, i});
            }
        }

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int newR = r + dr[i];
                int newC = c + dc[i];
                if (newR < 0 || newR >= m || newC < 0 || newC >= n || board[newR][newC] != 'O')
                    continue;
                board[newR][newC] = 'P';
                q.push({newR, newC});
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'P')
                    board[i][j] = 'O';
            }
        }
    }
};
// check if O region is surrouned by X (O cant reach edge)
// reformulate: bfs of O from edges (O->P)
// change all remaining O->X
// change back all P->O