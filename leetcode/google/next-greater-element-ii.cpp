#include <stack>
#include <vector>

class Solution {
  public:
    // monotonic stack
    std::vector<int> nextGreaterElements(std::vector<int> &nums) {
        std::stack<std::pair<int, int>> stk;
        int n = nums.size();
        std::vector<int> ans(n, -1);

        for (int i = 0; i < 2 * n; i++) {
            int i2 = i % n;
            while (!stk.empty() && stk.top().first < nums[i2]) {
                auto [num, idx] = stk.top();
                stk.pop();
                ans[idx] = nums[i2];
            }
            stk.push({nums[i2], i2});
        }
        return ans;
    }
};

// nums = [1,2,3,4,3]
// {} {(1,0)}
// {(1,0)} {(2,1)}, ans=[2,,,,,]
// {(3,2)}, ans=[2,3,,,,]
// {(4,3)}, ans=[2,3,4,,,]
// {(4,3), (3,4)}, ans=[2,3,4,,,]
// after 1st loop, clear stack

// [2,3,4,-1,4]

// 1: [], [2,3,4,3]
// 2: [1], [3,4,3]
// 3: [1,2], [4,3]

// [(1,0),(2,1),(3,2),(4,3),(3,4)]
// [(4,3),(3,2),(3,4),(2,1),(1,0)]

// idx i, nums[i], find nums[j] > nums[i];
// 1. first nums[j] to the right (j>i) ||
// 2. nums[j] to the left (j<i), where j is minimum
