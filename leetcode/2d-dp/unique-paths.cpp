#include <vector>

class Solution {
  public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1)
            return 1;

        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; i++)
            dp[i][0] = 1;
        for (int i = 0; i < n; i++)
            dp[0][i] = 1;

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
// 3x7 : 28
// robot must always move 2 downs, 6 rights to get to bottom right
// arrange ddrrrrrr on a line: 8!/(2!6!) = 7*8/2 = 28

// 3x2 : 6

// m=100, n=100, 99d, 99r: 198!/(99!99!) = 100*...198 / (1*2*..99)

// dp[0][0]= 1, dp[0][i]=1, dp[i][0]=1
// dp[i][j] = dp[i-1][j] + dp[i][j-1]
// return dp[m-1][n-1]