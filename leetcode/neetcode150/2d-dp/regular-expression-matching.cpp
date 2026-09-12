#include <string>
#include <vector>

class Solution {
  public:
    bool isMatch(std::string s, std::string p) {
        int m = s.size();
        int n = p.size();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;
        // dp[i][j] = true means "first i characters of s match first j characters of p"

        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) { // pattern must use at least 1 char to match anything in s
                if (p[j - 1] == '*') {
                    // * operates on the character BEFORE it (p[j-2]).
                    // imagine a* (* is superscripted)

                    // 1. MATCH 0 OCCURRENCES
                    //      ignore x* (p[j-2,j-1]), check if s[0...i-1] matched p[0...j-3]: dp[i][j-2]

                    // 2. MATCH 1+ OCCURRENCES
                    //      s[i-1] matches char before *: s[i-1] == p[j-2] || p[j-2] == '.'
                    //      AND s[0...i-2] matches p[0...j-1] (that same x* pattern might need to match s[i-2], s[i-3],
                    //      and so on)
                    dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
                } else { // p[i-1] == '.' or abc
                    // prev prefixes must match: dp[i-1][j-1]
                    // current chars match: s[i-1] == p[j-1] || p[j-1] == '.'
                    dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }

        return dp[m][n];
    }
};
// .=1
// *=0-n
// s = "aa", p = "a"
// s = "aa", p = "a*"
// s = "ab", p = ".*"

// dp[i+1][j+1] = s[0:i) and p[0:j) match
// dp[0][0] = "" and "" match = true
// for i: 0-s.size(), for j: 0-p.size()
// if p[j] == '*', dp[i][j] = dp[i-1][j-1]
// p[j]=='.', dp[i][j]
// else check if p[j]==s[i]