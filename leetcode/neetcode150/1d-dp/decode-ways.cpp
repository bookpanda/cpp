#include <string>

class Solution {
  public:
    int numDecodings(std::string s) {
        if (s.empty() || s[0] == '0')
            return 0;

        int prev2 = 1; // empty string
        int prev1 = 1; // first char not 0

        for (int i = 1; i < s.size(); i++) {
            int curr = 0;

            if (s[i] != '0')
                curr += prev1;

            int twoDigit = (s[i - 1] - '0') * 10 + (s[i] - '0');
            if (10 <= twoDigit && twoDigit <= 26)
                curr += prev2;

            if (curr == 0)
                return 0;
            prev2 = prev1;
            prev1 = curr;
            // cout << "dp[" << i << "] = " << dp[i] << "\n";
        }

        return prev1;
    }
};
// 1-9 -> ok
// 10 - 26 ->
// >=27 -> split

// "25" -> 2,5 or 25
// 226 -> 2,2,6 | 22,6 | 2,26
// 2|26 -> 2|26, 2|2|6
// 22|6 -> 22|6
// dp[i] = no. of ways to split s[0,i] = A + B
// A = dp[i-1] if dp[i] is valid (1-9) else 0
// B = dp[i-2] if dp[i-1,i] is valid (10-26) else 0
// 226, dp[0]=1, dp[1]=2
// dp[2] = A+B = 3
// A = 2 (22 | 6 -> 1<=6<=9)
// B = 1 (2 | 26 -> 10<=26<=26)

// 06, 60 -> 0 ways