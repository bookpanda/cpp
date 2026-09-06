#include <vector>

class Solution {
  public:
    int jump(std::vector<int> &nums) {
        int n = nums.size();
        int steps = 0, quota = 0, reach = 0;

        for (int i = 0; i < n; i++) {
            if (i > quota) { // refill
                quota = reach;
                steps++;
            }
            reach = std::max(reach, i + nums[i]);
        }
        return steps;
    }
};
// [2,3,1,1,4]
// dp[0]=0, dp[1/2]=1
// dp[1]=1, dp[3/4]=2

//  0 1 2 3 4 5 6 7 8 9
// [3,4,5,1,6,2,2,1,1,1]
//  ^ q=3
//.   ^ q=3->2, see 4 (dont refill yet, but remember)
//.     ^ q=2->1 see 5 (overwrite 4, dont refill yet)
//.       ^ q=1->0, remeber prev 5 (offset 1), so refill 5-1 = 4
//          ^ q=4->3, see 6
//            ^ q=3->2, see 2 (dont overwrite bc, 6-1 > 2)
//              ^ q=2->1, see 2  (dont overwrite bc, 6-2 > 2)
//                ^ q=1->0, see 1 (dont overwrite bc 6-3>1), but refill 6-3=3
//                  ^ q=3->2, see 1, remeber
//                    ^ q=2->1,
// dp[0]=0, dp[1/2/3]=1
// dp[1]=1, dp[4/5]=2
// dp[2]=1, dp[6/7]=2
// dp[3]=1
// dp[4]=2, dp[8/9/10]=3

// [2,3,1,1,4]
//. ^ q=2
//.   ^ q=2->1, see 3, refill
//.     ^ q=3->2
//         ^ q=2->1
//           ^ q=1->0
// did 2 refills: 1 at start, 1 at 3 (2 jumps)

// [2,3,0,1,4]
//  ^
//.   ^ q=2->1, see, 3 refill
//      ^ q=3->2
//        ^ q=2->1
//           ^ q=1->0

// [5,6,7]
//. ^ q=5
//.   ^ q=5->4, refill 6
//      ^ q=6->5

// [3,4,5,1,6,2,2,1,1,1]
// 1. check if can reach end on current step
// 2. if not, then refill?