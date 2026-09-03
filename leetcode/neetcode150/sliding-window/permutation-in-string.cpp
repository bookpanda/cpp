#include <string>
#include <vector>

class Solution {
  public:
    bool checkInclusion(std::string s1, std::string s2) {
        size_t n1 = s1.length(), n2 = s2.length();
        // cout << n1 << ", " << n2 << "\n";
        if (n2 < n1)
            return false;

        std::vector<int> s1Count(26, 0);
        std::vector<int> s2Count(26, 0);
        // fixed window size n1
        for (size_t i = 0; i < n1; i++) {
            s1Count[s1[i] - 'a']++;
            s2Count[s2[i] - 'a']++;
        }

        int match = 0;
        for (size_t i = 0; i < 26; i++) {
            if (s1Count[i] == s2Count[i])
                match++;
        }
        if (match == 26)
            return true;

        for (size_t i = n1; i < n2; i++) {
            size_t chIdx = s2[i] - 'a';

            s2Count[chIdx]++;
            if (s2Count[chIdx] == s1Count[chIdx]) {
                match++;
            } else if (s2Count[chIdx] == s1Count[chIdx] + 1) {
                match--;
            }

            chIdx = s2[i - n1] - 'a';
            s2Count[chIdx]--;
            if (s2Count[chIdx] == s1Count[chIdx]) {
                match++;
            } else if (s2Count[chIdx] == s1Count[chIdx] - 1) {
                match--;
            }
            // cout << "i=" << i << ", match=" << match << "\n";

            if (match == 26)
                return true;
        }

        return match == 26;
    }
};
// s2 contains substring of permutation of s1
// s1: a:1, b:1
// eidobaooo
//     s
//      i
// true

// eidboaoo