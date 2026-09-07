#include <deque>
#include <stack>
#include <string>

class Solution {
  public:
    bool checkValidString(std::string s) {
        std::stack<int> stk;
        std::deque<int> star;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '*') {
                star.push_back(i);
            } else if (c == '(') {
                stk.push(i);
            } else if (c == ')') {
                if (!stk.empty())
                    stk.pop();
                else {
                    if (star.size() == 0)
                        return false;
                    star.pop_front();
                }
            }
        }
        // opening brackets w/ no match , but have leftover stars
        while (!stk.empty() && !star.empty()) {
            if (stk.top() > star.back())
                return false;
            stk.pop();
            star.pop_back();
        }

        return stk.empty();
    }
};

// ( -> push {(, idx}
// ) -> check if top is ), yes: pop, no: check if quota>0
// quota >0: quota.pop_front()
// quota==0: return false
// * -> quota.push_back(idx)

// to solve: opening brackets w/ no match , but have quota (*(), (*)
// check if each {(,idx} and quota.back() idx2
// if idx2 > idx: quota.pop_back, stk.pop(), else return false
// return true

// (*) -> [], q=1
// (*)) -> [)], q=0 | [)],q=1 | [],q=1 | [],q=0

// "(*)"
// ( -> )
// * -> )*
// ) ->

// DOESNT WORK
// left=0, right=n-1
// works if left is ( or * && right is ) or *
// ((*)())
// ^     ^
//  ^   ^