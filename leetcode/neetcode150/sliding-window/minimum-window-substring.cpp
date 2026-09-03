#include <string>
#include <vector>

class Solution {
  public:
    std::string minWindow(std::string s, std::string t) {
        std::vector<int> tCount(256, 0);
        for (size_t i = 0; i < t.length(); i++) {
            tCount[t[i]]++;
        }

        std::vector<int> window(256, 0);
        std::string minStr = "";
        size_t minLength = INT_MAX;
        int match = 0;
        for (size_t i = 0; i < 256; i++) {
            if (tCount[i] == 0)
                match++;
        }

        size_t left = 0;
        for (size_t i = 0; i < s.length(); i++) {
            window[s[i]]++;
            if (window[s[i]] == tCount[s[i]]) {
                match++;
            }

            while (window[s[left]] > tCount[s[left]]) {
                window[s[left]]--;
                // if (window[s[left]] == tCount[s[left]] - 1) {
                //     match--;
                // }
                left++;
            }

            // cout << s[i] << ", match " << match << "\n";
            if (match == 256) {
                size_t length = i - left + 1;
                if (length < minLength) {
                    minLength = length;
                    minStr = s.substr(left, length);
                    // cout << "minStr " << minStr << "\n";
                }
            }
            // 01234567890
            // abc
            //  l
            //  i
            // match 255
            // window: a:0, b:1
            // tCount: b:1
        }

        return minStr;
    }
};

// ADOBECODEBANC
// l
//             i
// window: A:0, B:0, C:0
// tCount: A:1, B:1, C:1
// when window reachs s[i] (right side), cut window from left until it has satisfy minimum requirement (have all chars
// in t)