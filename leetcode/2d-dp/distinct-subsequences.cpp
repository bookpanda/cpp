#include <cstdint>
#include <string>
#include <vector>

class Solution {
  public:
    int numDistinct(std::string s, std::string t) {
        int ls = s.size(), lt = t.size();
        std::vector<std::vector<uint64_t>> dp(ls + 1, std::vector<uint64_t>(lt + 1, 0));
        dp[0][0] = 1;
        for (int i = 0; i <= ls; i++) {
            dp[i][0] = 1;
        }
        // for (int i=0;i<=lt;i++) {
        //     dp[0][i] = 0;
        // }

        for (int i = 1; i <= ls; i++) {
            for (int j = 1; j <= lt; j++) {
                dp[i][j] += dp[i - 1][j];
                if (s[i - 1] == t[j - 1])
                    dp[i][j] += dp[i - 1][j - 1];
            }
        }
        return static_cast<int>(dp[ls][lt]);
    }
};
// dp[i][j] = no. of subseq of s[0..i) that is == t[0..j)
// dp[0][0] = 1 "" ""
// dp[i][j] += dp[i-1][j]
// if (s[i]==t[j]) dp[i][j] += dp[i-1][j-1]