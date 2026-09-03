#include <string>

class Solution {
  public:
    int lengthOfLongestSubstring(std::string s) {
        if (s.length() == 0)
            return 0;

        // std::unordered_set<char> seen;
        bool seen[300] = {0};
        size_t start = 0;
        // seen.insert(s[0]);
        seen[s[0]] = true;
        size_t longest = 1;

        for (size_t i = 1; i < s.length(); i++) {
            // while (seen.find(s[i]) != seen.end()) {
            while (seen[s[i]]) {
                // seen.erase(s[start]);
                seen[s[start]] = false;
                start++;
            }

            // seen.insert(s[i]);
            seen[s[i]] = true;
            longest = std::max(longest, i - start + 1);
        }
        // a b c d a c d b
        //         s     i
        // seen: a c d b
        // longest 4

        return static_cast<int>(longest);
    }
};

// a b c d a c d b
//         l     r
// when r sees duplicate char, move l++ until it removes that char from seen set
// seen:  a c d
// longest: 4