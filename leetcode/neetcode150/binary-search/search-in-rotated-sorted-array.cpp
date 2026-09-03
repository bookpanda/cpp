#include <vector>

class Solution {
  public:
    int search(std::vector<int> &nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {
            int mid = (high + low) / 2;
            if (nums[mid] == target)
                return mid;

            if (nums[low] <= nums[mid]) { // nums[l..m] is sorted
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid - 1; // target is in nums[l..m-1]
                } else {
                    low = mid + 1; // target is in nums[m+1..h]
                }
            } else { // nums[low] > nums[mid] = there's a drop in nums[l..m], no drop in nums[m..h]
                     // nums[m..h] is sorted
                if (nums[mid] < target && target <= nums[high]) {
                    low = mid + 1; // target is in nums[m+1..h]
                } else {
                    high = mid - 1; // target is in nums[l..m-1]
                }
            }
        }

        return -1;
    }
};
// [3,1] (target=1)
//  l0,h1,m0

// [1,3] (target=2)
//  lmh
// l0,m0,h1
// l1,m1,h1

// 4,5,6,7,0,1,2 (target=0)
// l.    m.    h
//         l m h
//         lmh

// [1], target=0
// l0,h0,m0

// BS: h=n-1, l=0, m=(h+l)/2
// 4,5,6,7,0,1,2 (target=4)
// l     m     h

// arr = nums[l..h] for current l, h
// 1. whole arr is sorted (as if no rotations) = 1 asc arr
// 2. whole arr not sorted = 2 asc arrays stuck together (1 drop in value)
// e.g. 4,5,6,7 and 0,1,2 (drop be 7,0)

// if nums[m] == target: return m
// nums[l] < nums[m]: nums[l..m] is sorted
// if nums[l] <= target <= nums[m]: target is in nums[l..m]
// else target is in nums[m+1..h]

// nums[m] < nums[h]: nums[m..h] is sorted