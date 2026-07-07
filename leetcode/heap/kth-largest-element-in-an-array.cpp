#include <queue>
#include <vector>

class Solution {
  public:
    int findKthLargest(std::vector<int> &nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
        for (int num : nums) {
            heap.push(num);
            if (heap.size() > k)
                heap.pop();
        }
        return heap.size() > 0 ? heap.top() : -1;
    }
};

// [3,2,1,5,6,4], k=2
// {5,6}, min heap

// [3,2,3,1,2,4,5,5,6], k = 4
// {4,5,5,6}