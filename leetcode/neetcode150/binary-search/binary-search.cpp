#include <vector>

class Solution {
  public:
    int search(std::vector<int> &nums, int target) {
        int high = nums.size() - 1;
        int low = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            // cout << "low " << low << ", high " << high << "\n";
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
};