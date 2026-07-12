#include <string>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<std::string>> partition(std::string s) {
        std::vector<std::string> path;
        backtrack(s, 0, path);

        return ans;
    }

  private:
    std::vector<std::vector<std::string>> ans;
    void backtrack(const std::string &s, int start, std::vector<std::string> &path) {
        if (start == s.length()) {
            ans.push_back(path);
            return;
        }

        for (int i = start; i < s.length(); i++) {
            if (isPalindrome(s, start, i)) {
                path.push_back(s.substr(start, i - start + 1));
                backtrack(s, i + 1, path);
                path.pop_back();
            }
        }
    }

    bool isPalindrome(const std::string &s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--])
                return false;
        }
        return true;
    }
};