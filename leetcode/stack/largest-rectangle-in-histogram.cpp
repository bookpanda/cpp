#include <algorithm>
#include <stack>
#include <vector>

class Solution {
  public:
    int largestRectangleArea(std::vector<int> &heights) {
        int n = heights.size();
        std::vector<int> left(n), right(n);

        std::stack<std::pair<int, int>> stk;
        // ascending stack (right)
        for (int i = 0; i < heights.size(); i++) {
            if (stk.empty() || stk.top().first < heights[i]) {
                stk.push({heights[i], i});
                continue;
            }

            while (!stk.empty() && stk.top().first > heights[i]) {
                right[stk.top().second] = i;
                stk.pop();
            }
            stk.push({heights[i], i});
        }
        while (!stk.empty()) {
            right[stk.top().second] = n;
            stk.pop();
        }

        // ascending stack (from right side) (left)
        for (int i = n - 1; i >= 0; i--) {
            if (stk.empty() || stk.top().first < heights[i]) {
                stk.push({heights[i], i});
                continue;
            }

            while (!stk.empty() && stk.top().first > heights[i]) {
                left[stk.top().second] = i;
                stk.pop();
            }
            stk.push({heights[i], i});
        }
        while (!stk.empty()) {
            left[stk.top().second] = -1;
            stk.pop();
        }

        // cout << "left: ";
        // for (auto l : left) {
        //     cout << l << " ";
        // } cout << "\nright: ";
        // for (auto l : right) {
        //     cout << l << " ";
        // } cout << "\n";

        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            int area = heights[i] * (right[i] - left[i] - 1);
            maxArea = std::max(area, maxArea);
        }

        return maxArea;
    }
};

// stack, stk.size() = width
// for (heights), heights[i] = right most bar for the rectangle

// 5, 6
// 5, 10, 10: 5x3 or 10x2

// stack is ascending [(height, length)]
// when find new bar that is lower than stk.top(), merge previous ones
// merge = pop stk until stk.top() < new bar
// [(2,1)]
// [(1,2)] merged
// [(1,2),(5,1)] -> 2
// [(1,2),(5,1),(6,1)] -> 10
// [(1,2),(2,3)] -> 6 merged
// [(1,2),(2,3),(3,1)] -> 8
// problem: [(1,100),(2,45),(3,30)...]