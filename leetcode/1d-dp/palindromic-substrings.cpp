#include <string>

class Solution {
  public:
    int countSubstrings(std::string s) {
        int n = s.size();
        int count = 0;

        auto expand = [&](int left, int right) {
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;
                left--;
                right++;
            }
        };

        for (int i = 0; i < n; i++) {
            expand(i, i);     // length is odd
            expand(i, i + 1); // length is even
        }

        return count;
    }
};
// aaa
// e(0,0), e(0,1): a | aa
// e(1,1), e(1,2): a, aaa | aa
// e(2,2), e(2,3): a |

// abba
// e(0,0), e(0,1): a |
// e(1,1), e(1,2): b | bb, abba
// e(2,2), e(2,3): b |
// e(3,3), e(3,4): a |

// naive: O(n^3): for start idx and end idx, then check if s[start,end] is palin
// better: O(n^2): expanding from center: for each center , then expend center while it is still palindrome
// also it is O(1) in space,
// time; best O(n) asdfg, worst O(n^2) aaaaaaa
// manacher: time/space both O(n)