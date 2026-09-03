#include <vector>

class Solution {
  public:
    std::vector<int> plusOne(std::vector<int> &digits) {
        std::vector<int> ans;
        int carry = 1;
        for (int i = digits.size() - 1; i >= 0; i--) {
            int sum = digits[i] + carry;
            ans.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry)
            ans.push_back(1);
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};