#include <queue>
#include <vector>

class Solution {
  public:
    int lastStoneWeight(std::vector<int> &stones) {
        std::priority_queue<int> heap;
        for (int stone : stones)
            heap.push(stone);

        while (heap.size() > 1) {
            int stone1 = heap.top();
            heap.pop();
            int stone2 = heap.top();
            heap.pop();
            if (stone1 == stone2)
                continue;
            heap.push(stone1 - stone2);
        }
        return heap.size() == 1 ? heap.top() : 0;
    }
};