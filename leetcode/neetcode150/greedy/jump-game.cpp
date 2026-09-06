#include <algorithm>
#include <vector>

class Solution {
  public:
    bool canJump(std::vector<int> &nums) {
        int quota = nums[0];
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            // move to idx i
            if (quota == 0)
                return false;
            quota--;
            // reached idx i
            quota = std::max(quota, nums[i]);
        }
        return true;
    }
};

// [2,3,1,1,4]
//. ^ q=2
//    ^ q=1 , see 3, so we "refill" q to 3
//.     ^ q=3->2, see 1 (dont refill since 1 < 2)
//        ^ q=2->1, see (dont refill since 1==1)
//           ^ q=1->0, see 4, refill, q=4

// [3,2,1,0,4]
//. ^ q=3
//.   ^ q=3->2, see 2 (dont refill, since 2==2)
//.     ^ q=2->1, see 1
//        ^ q=1->0, see 0, dont refill (cant move anymore = stuck = cant get to the end, return false)