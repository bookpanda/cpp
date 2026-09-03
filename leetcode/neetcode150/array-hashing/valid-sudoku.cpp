#include <cstdint>
#include <vector>

class Solution {
  public:
    bool isValidSudoku(std::vector<std::vector<char>> &board) {
        // row, col, grid
        // highly optimized space-efficient (pack bools into individual bits) so
        // CPU cannot reference them directly (need bitwise shifts + masks)
        // vector is also array of pointers
        // std::vector<std::vector<bool>> rows(9, std::vector<bool>(9, false));

        // optimization: use normal arrays + bitmask on int
        uint16_t rows[9] = {0};
        uint16_t cols[9] = {0};
        uint16_t grids[9] = {0};

        for (size_t r = 0; r < 9; r++) {
            for (size_t c = 0; c < 9; c++) {
                // board[r][c]
                if (board[r][c] == '.') {
                    continue;
                }

                int mask = 1 << (board[r][c] - '1'); // '1'= 1<<0, '9'= 1<<8
                int gridIdx = (r / 3) * 3 + (c / 3);
                if ((rows[r] & mask) || (cols[c] & mask) || (grids[gridIdx] & mask)) { // duplicate
                    return false;
                }
                rows[r] |= mask;
                cols[c] |= mask;
                grids[gridIdx] |= mask;
            }
        }
        return true;
    }
};