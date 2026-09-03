#include <vector>

class Solution {
  public:
    std::vector<int> countBits(int n) {
        std::vector<int> ans = {0};
        for (int i = 1; i <= n; i++) {
            if (i & 1) { // 101 -> 10 + 1
                ans.push_back(ans[i >> 1] + 1);
            } else { // 100 -> 10
                ans.push_back(ans[i >> 1]);
            }
        }

        return ans;
    }
};
// 0 -> n
// 0, 1, 2, 3, 4, 5, 6, 7, 8
// 0, 1, 10, 11, 100, 101, 110, 111, 1000
//