#include <algorithm>
#include <vector>

class Solution {
  public:
    int maxArea(std::vector<int> &height) {
        size_t left = 0;
        size_t right = height.size() - 1;
        size_t maxArea = 0;

        while (left < right) {
            size_t leftHeight = height[left];
            size_t rightHeight = height[right];

            size_t area = (right - left) * std::min(leftHeight, rightHeight);
            maxArea = std::max(maxArea, area);

            if (leftHeight <= rightHeight) {
                // optimize: skip shorter sticks
                left++;
                while (left < right && height[left] <= leftHeight)
                    left++;
            } else if (rightHeight < leftHeight) {
                right--;
                while (left < right && height[right] <= rightHeight)
                    right--;
            }
        }
        // [1,8,6,2,5,4,8,3,7]
        //             lr
        // maxArea 49
        return maxArea;
    }
};

// cant sort
// left, right are most furthest apart (max width)
// if height[left+1] < height[left]: dont take
// if height[left+1] > height[left]: can try take
// always change the shorter stick
// if height[left] < height[right]: left++