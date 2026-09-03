#include <algorithm>
#include <string>
#include <vector>

class Solution {
  public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        std::vector<std::vector<int>> dp(text1.size(), std::vector<int>(text2.size(), 0));
        // return lcs(text1, 0, text2, 0, dp);

        int m = text1.size(), n = text2.size();
        if (text1[0] == text2[0])
            dp[0][0] = 1;
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0];
            if (text1[i] == text2[0])
                dp[i][0] = std::max(dp[i][0], 1);
        }
        for (int i = 1; i < n; i++) {
            dp[0][i] = dp[0][i - 1];
            if (text1[0] == text2[i])
                dp[0][i] = std::max(dp[0][i], 1);
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (text1[i] == text2[j]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m - 1][n - 1] == -1 ? 0 : dp[m - 1][n - 1];
    }

  private:
    int lcs(const std::string &text1, int i, const std::string &text2, int j, std::vector<std::vector<int>> &dp) {
        if (i == text1.size() || j == text2.size())
            return 0;
        if (dp[i][j] != -1)
            return dp[i][j];

        if (text1[i] == text2[j]) {
            // cout << "text1: " << text1[i] << ", text2: " << text2[j] << "\n";
            dp[i][j] = 1 + lcs(text1, i + 1, text2, j + 1, dp);
            return dp[i][j];
        }
        dp[i][j] = std::max(lcs(text1, i + 1, text2, j, dp), lcs(text1, i, text2, j + 1, dp));
        return dp[i][j];
    }
};
//   a b c d e, ace
// a 1 1 1 1 1
//.c 1 1 2 2 2
//.e 1 1 2 2 3
// dp[i][j] = LCS of s1[0..i], s2[0..j]
// dp[i][j] = max(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) (+ 1 if s1[i]==s2[j])

//  a b c
// a 1 1 1
// b 1 2 2
// c 1 2 3
