#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    bool wordBreak(std::string s, std::vector<std::string> &wordDict) {
        int n = s.size();
        std::vector<bool> dp(n + 1, false);
        dp[0] = true;

        size_t maxLen = 0;
        for (const auto &word : wordDict) {
            maxLen = std::max(maxLen, word.size());
        }

        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());

        for (int i = 1; i <= n; i++) {
            int lastLen = std::min(static_cast<size_t>(i), maxLen);
            for (int len = 1; len <= lastLen; len++) {
                std::string subStr = s.substr(i - len, len);
                if (dp[i - len] && dict.count(subStr)) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
// s = "catsandog", wordDict = ["cats","dog","sand","and","cat"], longestWordLen=4
// i=0, j=0:
// i=1, j=0..1
// i=2, j=0..2, dp[2]=true
// i=3, j=0..3, dp[3]=true
// i=4, j=1..4
// i=5, j=2..5
// i=6, j=3..6, j=3: sand & dp[2], dp[6], j=4: and & dp[3], dp[6]
// i=7, j=4..7
// i=8, j=5..8, j=6: dog & !dp[5]

// dp[i] = true means s[0..i] can be cut into words in wordDict
// leetcode, wordDict = ["leet","code"]
// dp[3] = true -> "leet"
// when we're at idx 7 , can check s[4..7] "code" is in wordDict and check dp[3]==true
// when we're at idx i, can check s[j..i] (j is [i-20,i]) if it's in dict and check dp[j-1]==true

// return dp[n-1]