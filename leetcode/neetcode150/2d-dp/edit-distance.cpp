#include <algorithm>
#include <string>
#include <vector>

class Solution {
  public:
    int minDistance(std::string word1, std::string word2) {
        int n = word1.size(), m = word2.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
        for (int i = 0; i <= n; i++)
            dp[i][0] = i; // delete from word1
        for (int i = 0; i <= m; i++)
            dp[0][i] = i; // add to word1

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                    continue;
                }
                // replace in word1, delete from word1, insert to word1
                dp[i][j] = std::min(dp[i - 1][j - 1], std::min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }
        return dp[n][m];
    }
};
// word1 = "horse", word2 = "ros"
// dp[i][j] = ED from word1[0..i) to word2[0..j)