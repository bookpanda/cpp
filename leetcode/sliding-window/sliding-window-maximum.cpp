#include <deque>
#include <vector>

class Solution {
  public:
    std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
        int n = nums.size();
        std::deque<int> dq;

        std::vector<int> window;
        for (int i = 0; i < n; i++) {
            int st = i - k + 1;
            // clear old ones fron front (out of range)
            while (!dq.empty() && dq.front() < st)
                dq.pop_front();

            // clear inferior ones from back
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);

            if (i >= k - 1)
                window.push_back(nums[dq.front()]);
        }

        return window;
    }
};