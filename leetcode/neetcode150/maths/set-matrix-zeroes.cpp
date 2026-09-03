#include <vector>

class Solution {
  public:
    void setZeroes(std::vector<std::vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool isTopRowZero = false, isLeftColZero = false;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                    if (i == 0)
                        isTopRowZero = true;
                    if (j == 0)
                        isLeftColZero = true;
                }
            }
        }

        for (int j = 1; j < n; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 0; i < m; i++)
                    matrix[i][j] = 0;
            }
        }
        for (int i = 1; i < m; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 0; j < n; j++)
                    matrix[i][j] = 0;
            }
        }

        if (isTopRowZero)
            for (int j = 0; j < n; j++)
                matrix[0][j] = 0;
        if (isLeftColZero)
            for (int i = 0; i < m; i++)
                matrix[i][0] = 0;
    }
};
// m[i][j] = 0 -> make m[0][j]=0 and m[i][0]=0

// loop only 1st row and 1st col
// 1st row: if m[0][j]==0, fill entire col as 0 (m[i][j])
// 1st col: if m[i][0]==0, fill entire row as 0 (m[i][j])

// 1234. 0030
// 5078  0078
// 0111. 0110
// 1110. 0110
