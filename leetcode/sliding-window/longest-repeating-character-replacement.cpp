#include <algorithm>
#include <string>
#include <vector>

class Solution {
  public:
    int characterReplacement(std::string s, int k) {
        int lcr = 0;
        // window length - count of most freq char <= k
        std::vector<int> count(26, 0);
        size_t start = 0;
        int maxFreq = 0;

        for (size_t i = 0; i < s.length(); i++) {
            size_t idx = s[i] - 'A';
            count[idx]++;
            maxFreq = std::max(maxFreq, count[idx]);

            // cut substring from left
            if ((i - start + 1) - maxFreq > k) {
                count[s[start] - 'A']--;
                start++;
            }

            lcr = std::max(lcr, static_cast<int>(i - start + 1));
        }
        // cout << ch << ": " << lcr << "\n";
        // 0123
        // ABAB
        //   i
        // A: start=1, substituted={},
        // 012345678
        // AABCBCAAB, k = 2
        //    i
        // A: start=5, substituted={5, 8},
        // B: start=1, substituted={1,3},
        // C: start=0, substituted={},
        // lcr = 4

        return lcr;
    }
};

// ABAB -> AAAA, BBBB
// AABABBA -> AAAABBA, AABBBBA
// A-Z (26) * 100k = 2.6M -> forA-Z, for(characterReplacement, s, into char)
// AABAABA change any char into A
// keep count + postions of substituted chars