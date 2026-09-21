#include <vector>

class Solution {
  public:
    int singleNonDuplicate(std::vector<int> &nums) {
        int n = nums.size();
        int low = 0, high = n - 1, mid;

        while (low <= high) {
            mid = (high + low) / 2;
            if (mid + 1 < n && nums[mid] == nums[mid + 1]) {
                if (mid & 1) { // AFTER
                    high = mid - 1;
                } else { // BEFORE
                    low = mid + 1;
                }
            } else if (mid - 1 >= 0 && nums[mid] == nums[mid - 1]) {
                if (mid & 1) { // BEFORE
                    low = mid + 1;
                } else { // AFTER
                    high = mid - 1;
                }
            } else { // doesn't match either nums[mid-1] nor nums[mid+1]
                break;
            }
        }
        return nums[mid];
    }
};
