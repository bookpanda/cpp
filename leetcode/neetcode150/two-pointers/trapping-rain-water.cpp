#include <vector>

class Solution {
  public:
    int trap(std::vector<int> &height) {
        size_t left = 0;
        size_t right = height.size() - 1;
        int water = 0;

        while (left < right) {
            size_t leftHeight = height[left];
            size_t rightHeight = height[right];

            if (leftHeight <= rightHeight) {
                left++;
                while (left < right && height[left] < leftHeight) {
                    water += leftHeight - height[left];
                    left++;
                }
            } else {
                right--;
                while (left < right && height[right] < rightHeight) {
                    water += rightHeight - height[right];
                    right--;
                }
            }
        }
        // [0,1,0,2,1,0,1,3,2,1,2,1]
        //                lr
        // water 1+1+2+1 + 1

        return water;
    }
};

// [0,1,0,2,1,0,1,3,2,1,2,1]
//                lr
// edges l,r >=1 : (move shorter one) l++ until height[newl] >= height[l]
// along the way, add up water if height[newl] < height[l]
// water: 1+1+2+1 + 1