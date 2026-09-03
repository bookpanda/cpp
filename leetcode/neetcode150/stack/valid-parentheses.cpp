#include <stack>
#include <string>

class Solution {
  public:
    bool isValid(std::string s) {
        if (s.length() & 1)
            return false;

        // std::vector as the backend for contiguous memory performance
        std::stack<char, std::vector<char>> stk;

        for (char c : s) {
            switch (c) {
            case '(':
                stk.push(')');
                break;
            case '[':
                stk.push(']');
                break;
            case '{':
                stk.push('}');
                break;
            default:
                if (!stk.empty() && stk.top() == c) {
                    stk.pop();
                    break;
                } else {
                    return false;
                }
            }
        }
        return stk.empty();
    }
};

// ()[]{}
// ([])
//