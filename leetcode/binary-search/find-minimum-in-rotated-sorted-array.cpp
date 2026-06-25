#include <vector>

class Solution {
  public:
    int findMin(std::vector<int> &nums) {
        int right = nums.size() - 1;
        int left = 0;

        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[left] > nums[right]) {
                if (nums[left] > nums[mid]) { // drop between l and m
                    right = mid;
                } else { // drop between m and r
                    left = mid + 1;
                }
            } else {
                return nums[left];
            }
        }
        return nums[left];
    }
};
// [11,13,15,17]
//. l  m     r

// [4,5,6,7,0,1,2]
//  l     m     r
//          l m r

// [3,4,5,1,2]
//. l   m   r
//.       lmr

// 0,1,2,4,5,6,7

// rotated = 2 ascending subarrays (have at most 1 drop from max to min value)
// 4,5,6,7,0,1,2
// l     m     r

// nums[l] > nums[r]: there is a drop between l and r (we dont know)
//      nums[l] > nums[m]: there is a drop between l and m = min value not in nums[m+1..r] (can cut)
//      nums[m] > nums[r]: there is a drop between m and r = min value not in nums[l..m] (can cut)
// else: nums[l] < nums[r]: return nums[l] since it is min value (nums[l..r] is sorted, no drops)

// nums[m] > nums[l]: nums[l..m] is ascending, min value not in nums[l..m]

// find min = find the