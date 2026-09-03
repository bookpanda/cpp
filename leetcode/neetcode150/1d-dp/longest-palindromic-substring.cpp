#include <string>

class Solution {
  public:
    std::string longestPalindrome(std::string s) {
        // writing expand around center time O(n^2), space O(1)
        // you could write Manacher's algo: time O(n), space O(n), but overkill
        int start = 0;
        int maxLen = 0;

        // [&] = captures all local vars in surrounding scope by ref (since need to modify start, maxLen)
        auto expand = [&](int left, int right) {
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                left--;
                right++;
            }
            int len = right - left - 1;
            if (maxLen < len) {
                maxLen = len;
                start = left + 1;
            }
        };

        for (int i = 0; i < s.size(); i++) {
            expand(i, i);     // odd length
            expand(i, i + 1); // even length
        }

        return s.substr(start, maxLen);
    }
};

// naive: for start and finish of substring , then check if palin (O(n^2))