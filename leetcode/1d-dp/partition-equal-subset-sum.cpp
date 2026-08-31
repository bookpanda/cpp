#include <algorithm>
#include <vector>

class Solution {
  public:
    bool canPartition(std::vector<int> &nums) {
        int halfSum = 0;
        int maxNum = 0;
        for (int num : nums) {
            halfSum += num;
            maxNum = std::max(maxNum, num);
        }
        if (halfSum % 2 == 1)
            return false; // sum(nums) is odd
        halfSum /= 2;
        if (maxNum > halfSum)
            return false;

        std::vector<bool> knap(halfSum + 1, false);
        knap[0] = true;

        for (int num : nums) {
            for (int j = halfSum; j >= num; j--) {
                if (j - num >= 0 && knap[j - num]) {
                    knap[j] = true;
                }
            }
            if (knap[halfSum])
                return true;
        }

        return knap[halfSum];
    }
};
// nums = [1,5,11,5], halfSum=11
//.        0 1 2 3 4 5 6 7 8 9 10 11
// knap = [t,t,0,0,0,t,t,0,0,0,t, t]

// worst 2^n: pick each num: group1 or group2
// sum(group1) == sum(group2) = 1/2 sum(nums)
// if 1/2 sum(nums) == odd -> return false
// 1/2 sum(nums) == even, could be cases (2,1,7)

// can we group some numbers from nums to group1 s.t. sum(group1) = 1/2 sum(nums)
// since the sum(rest)'d automatically be 1/2 sum(nums)

// 200 numbers, each <=100
// knapsack? knap[20000]
// knap[i] = can find sum==i using numbers from nums
// for i [1,20000]: knap[i] = true if knap[i-nums[j]]==true
// O(20k * 200) = 4M