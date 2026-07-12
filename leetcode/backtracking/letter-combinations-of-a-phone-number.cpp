#include <string>
#include <vector>

class Solution {
  public:
    std::vector<std::string> letterCombinations(std::string digits) {
        std::string str;
        combinations(digits, 0, str);
        return ans;
    }

  private:
    std::vector<std::string> ans;
    std::vector<std::string> chars = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    void combinations(std::string digits, int idx, std::string &str) {
        // cout << idx << ", " << str << "\n";
        if (idx == digits.size()) {
            ans.push_back(str);
            return;
        }

        for (char c : chars[digits[idx] - '0']) {
            str.push_back(c);
            combinations(digits, idx + 1, str);
            str.pop_back();
        }
    }
};