#include <stack>
#include <vector>

class Solution {
  public:
    std::vector<int> dailyTemperatures(std::vector<int> &temperatures) {
        std::stack<std::pair<int, int>> stk;
        std::vector<int> ans(temperatures.size());

        for (size_t i = 0; i < temperatures.size(); i++) {
            if (stk.empty()) {
                stk.push({temperatures[i], i});
                continue;
            }

            if (temperatures[i] <= stk.top().first) { // colder future
                stk.push({temperatures[i], i});
            } else { // warmer future
                while (!stk.empty() && stk.top().first < temperatures[i]) {
                    ans[stk.top().second] = i - stk.top().second;
                    stk.pop();
                }
                stk.push({temperatures[i], i});
            }
        }

        while (!stk.empty()) {
            ans[stk.top().second] = 0;
            stk.pop();
        }

        return ans;
    }
};

// []
// [73]
// [], [74] -> 1
// [], [75] -> 1, 1
// [75,71] -> 1, 1
// [75,71,69] -> 1, 1
// [75,71], [75], [75,72] -> 1, 1, _, 2, 1
// [75], [], [76] -> 1, 1, 4, 2, 1, 1
// [76,73] -> 1, 1, 4, 2, 1, 1
// -> 1, 1, 4, 2, 1, 1, 0, 0