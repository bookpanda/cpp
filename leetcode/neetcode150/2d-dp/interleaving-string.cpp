#include <string>
#include <vector>

class Solution {
  public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        if (s3.size() != s1.size() + s2.size())
            return false;
        if (s1.size() == 0 && s2 == s3)
            return true;
        if (s2.size() == 0 && s1 == s3)
            return true;
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();

        std::vector<std::vector<int>> dp(l1 + 1, std::vector<int>(l2 + 1, false));
        dp[0][0] = true;
        for (int i = 0; i < l1; i++) {
            if (s3[i] == s1[i] && dp[i][0])
                dp[i + 1][0] = true;
        }
        for (int i = 0; i < l2; i++) {
            if (s3[i] == s2[i] && dp[0][i])
                dp[0][i + 1] = true;
        }

        for (int i = 1; i <= l1; i++) {
            for (int j = 1; j <= l2; j++) {
                if (s3[i + j - 1] == s1[i - 1] && dp[i - 1][j]) {
                    // cout << "s1 i=" << i << ", j=" << j << "\n";
                    dp[i][j] = true;
                }
                if (s3[i + j - 1] == s2[j - 1] && dp[i][j - 1]) {
                    // cout << "s2 i=" << i << ", j=" << j << "\n";
                    dp[i][j] = true;
                }
            }
        }

        // for (int i=0;i<=l1;i++) {
        //     for (int j=0;j<=l2;j++) {
        //         if (dp[i][j]) cout << "dp["<<i<<"]["<<j<<"] ";
        //     }
        //     cout << "\n";
        // }

        return dp[l1][l2];
    }
};
// s1 = "aa|b|cc", s2 = "d|bb|ca", s3 = "aadbbbaccc"
// dp[0][0][0] = dp[0][0][1] = true = 0 chars from s1, s2 = can make 0 chars in s3
// k=1, i=1: dp[1][0][0],
// k=2, i=2: dp[2][0][0]
// k=3, s2: i=1: dp[2][1][1] = true
// dp[2][0][0] "aa"
// dp[2][1][1] "aad"
// dp[2][2][1] "aadb",  dp[3][1][0] "aadb"

// dp[i][j][0|1] = is interleaving of s1[0..i), s2[0..j) possible to make s3[0..i+j)?
// [0] = last position was substring of s1
// [1] = last position was substring of s2