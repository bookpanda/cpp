#include <string>
#include <vector>

class Solution {
  public:
    std::vector<std::string> ans;
    std::vector<std::string> generateParenthesis(int n) {
        std::string str;
        genParen(n, str, 0);
        return ans;
    }
    void genParen(int n, std::string &str, int offset) {
        if (str.length() == 2 * n) {
            if (offset == 0)
                ans.push_back(str);
            return;
        }

        // 1. insert (
        if (offset < n) { // always keep offset >= n
            str.push_back('(');
            genParen(n, str, offset + 1);
            str.pop_back();
        }

        // 2. insert )
        if (offset > 0) { // always keep offset >= 0
            str.push_back(')');
            genParen(n, str, offset - 1);
            str.pop_back();
        }
    }
};
// n=2 : (()), ()()
// gP(str,offset)
// gP("",0) -> gP("(",1)
// gP("(",1) -> gP("((",2), gP("()",0)
// gP("((",2) -> gP("(()",1)
// gP("()",0) -> gP("()(",1)
// gP("(()",1) -> gP("(()(",2), gP("(())",0)
// gP("()(",1) -> gP("()((",2), gP("()()",0)

// n pairs -> 2n characters
// f()
// 1. insert (
// 2. insert )
// O((2n)^2) = 16^2 = 64k