#include <algorithm>
#include <climits>
#include <vector>

class Solution {
  public:
    int maxSubArray(std::vector<int> &nums) { return dc(nums, 0, nums.size() - 1); }
    int dc(std::vector<int> &nums, int l, int r) {
        if (l == r)
            return nums[l];
        if (l > r)
            return INT_MIN;

        int mid = (l + r) / 2;
        int leftCall = dc(nums, l, mid);
        int rightCall = dc(nums, mid + 1, r);

        int midLeft = nums[mid];
        int maxLeft = midLeft;
        for (int i = mid - 1; i >= l; i--) {
            midLeft += nums[i];
            maxLeft = std::max(maxLeft, midLeft);
        }

        int midRight = mid + 1 >= nums.size() ? 0 : nums[mid + 1];
        int maxRight = midRight;
        for (int i = mid + 2; i <= r; i++) {
            midRight += nums[i];
            maxRight = std::max(maxRight, midRight);
        }

        int middleMax = maxLeft + maxRight;
        // cout << "["<<l<<", "<<r<<"]: ";
        // cout << "leftCall:"<<"["<<l<<","<<mid<<"]="<<leftCall;
        // cout << ", rightCall:"<<"["<<mid+1<<","<<r<<"]="<<rightCall;
        // cout << ", middleMax: "<< middleMax << "(left: " << maxLeft << ", right: " << maxRight << ")\n";
        return std::max(middleMax, std::max(leftCall, rightCall));
    }
};