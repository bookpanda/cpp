#include <string>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::string> board(n);
        for (std::string &row : board)
            row = std::string(n, '.');

        colUsed.resize(n, false);
        nQueens(n, 0, board, 0);

        return ans;
    }

  private:
    std::vector<std::vector<std::string>> ans;
    std::vector<bool> colUsed;
    void nQueens(int n, int lvl, std::vector<std::string> &board, int row) {
        if (lvl == n) {
            ans.push_back(board);
            return;
        }

        for (int c = 0; c < n; c++) {
            if (colUsed[c])
                continue;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                int nr = row - i;
                int nc = c + i;
                int nc2 = c - i;
                if (nr < 0)
                    break;
                if (nc >= 0 && nc < n && board[nr][nc] == 'Q') {
                    valid = false;
                    break;
                }
                if (nc2 >= 0 && nc2 < n && board[nr][nc2] == 'Q') {
                    valid = false;
                    break;
                }
            }

            if (!valid)
                continue;
            board[row][c] = 'Q';
            colUsed[c] = true;
            nQueens(n, lvl + 1, board, row + 1);
            colUsed[c] = false;
            board[row][c] = '.';
        }

        return;
    }
};
// nxn board
// each row/col/diag only 1Q (how to track?)
// for col: check !colUsed[c]
// check diag: for i in [0,n]: [r+i][c+i]
//  do 4 loops: (+i,+i), (+i,-i), (-i,+i), (-i,-i)

// 1x1: 2 * 1 diag lines
// 2x2: 2 * 3
// 3*3: 2 * 5