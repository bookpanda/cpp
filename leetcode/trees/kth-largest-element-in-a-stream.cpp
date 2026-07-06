#include <queue>
#include <vector>

class KthLargest {
  private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
    int cap;

  public:
    KthLargest(int k, std::vector<int> &nums) {
        cap = k;
        for (int num : nums) {
            heap.push(num);
            if (heap.size() > cap)
                heap.pop();
        }
    }

    int add(int val) {
        heap.push(val);
        if (heap.size() > cap)
            heap.pop();
        return heap.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */