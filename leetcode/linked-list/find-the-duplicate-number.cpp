#include <vector>

class Solution {
  public:
    int findDuplicate(std::vector<int> &nums) {
        // every value in the array is a valid index within the array
        int slow = nums[0];
        int fast = nums[nums[0]];
        // both will meet at a number, though not necessarily a duplicate
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        // x = distance from start to entrace of cycle
        // y = distance from entrace of cycle to point where slow/fast meet
        // c = length of cycle
        // slow traveled x+y
        // fast traveled x+y+k*c
        // fast is 2x faster: 2(x+y) = x+y+k*c, x+y = k*c, x = k*c-y
        // k*c-y = distance from where slow/fast meet to loop entrance (loop entrance = duplicate number)

        // so slow needs to move from start by x
        // and fast needs to move by k*c-y (same distance as x)
        // for them to meet at loop entrance (duplicate number)
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};
// 1->3->2->4(->2)
// duplicate = 2+ arrows to same node = loop
// [1,3,4,2,2]
//. s f
//    s f
//      f s
//      sf
//  s.    f
//    s f