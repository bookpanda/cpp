#include <vector>

class Solution {
  public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int high = (m * n) - 1;
        int low = 0;

        while (low <= high) {
            int mid = (high + low) / 2;
            int row = mid / n;
            int col = mid % n;
            if (matrix[row][col] == target)
                return true;
            if (matrix[row][col] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return false;
    }
};
// 3
// h 11, l 0 -> m5, r1, c1
// h 4, l 0 -> m2, r0, c2
// h 1, l 0 -> m0, r0, c0
// h 1, l 2 -> m1, r0, c1 -> found 3

// mid = (high + low) / 2
// 1D: high = n-1, low=0
// 2D: high = (m*n)-1, low=0, e.g. mid=7 (7/4=1, 7%4=3)