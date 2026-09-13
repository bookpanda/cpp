#include <algorithm>
#include <string>

class Solution {
  public:
    int longestValidParentheses(std::string s) {
        int left = 0, right = 0, maxLen = 0, n = s.size();

        // 1. left->right
        for (int i = 0; i < n; i++) {
            if (s[i] == '(')
                left++;
            else if (s[i] == ')')
                right++;

            if (left == right) {
                maxLen = std::max(maxLen, 2 * right);
            } else if (right > left) {
                left = 0;
                right = 0;
            }
        }

        left = right = 0;
        // (()
        // 2. right->left
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '(')
                left++;
            else if (s[i] == ')')
                right++;

            if (left == right) {
                maxLen = std::max(maxLen, 2 * right);
            } else if (right < left) {
                left = 0;
                right = 0;
            }
        }

        return maxLen;
    }
};