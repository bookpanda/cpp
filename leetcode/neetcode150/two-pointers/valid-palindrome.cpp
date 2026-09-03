#include <algorithm>
#include <cctype>
#include <string>

class Solution {
  public:
    void sanitizeString(std::string &str) {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });

        // std::remove_if does NOT delete, it just moves garbage to end
        auto garbageBegin = std::remove_if(str.begin(), str.end(), [](unsigned char c) { return !std::isalnum(c); });

        str.erase(garbageBegin, str.end());
    }

    bool isPalindrome(std::string s) {
        sanitizeString(s);

        auto left = s.begin();
        auto right = s.end() - 1;
        while (left < right) {
            if (*left != *right) {
                // cout << *left << " | " << *right;
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};