#include <queue>
#include <vector>

class MedianFinder {
  public:
    std::priority_queue<int> pq1;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq2;
    MedianFinder() {
        pq1.push(INT_MIN);
        pq2.push(INT_MAX);
    }

    void addNum(int num) {
        int n1 = pq1.top();
        int n2 = pq2.top(); // n1 <= n2
        if (num < n2) {
            pq1.push(num);
            if (pq1.size() - pq2.size() > 1) {
                pq2.push(pq1.top());
                pq1.pop();
            }
        } else {
            pq2.push(num);
            if (pq2.size() - pq1.size() > 0) {
                pq1.push(pq2.top());
                pq2.pop();
            }
        }
    }

    double findMedian() {
        if (pq1.size() == pq2.size())
            return (double)(pq1.top() + pq2.top()) / 2;
        // else (means pq1 has n+1, pq2 has n numbers)
        return pq1.top();
    }
};
// pq1=p0-p50, pq2=p50-p100
// pq1:maxHeap, pq2:minHeap
// 1: pq1[1] pq2[]
// 2: pq1[1] pq2[2]
// when addNum(num):
// pq1.top() = n1 around p50
// pq2.top() = n2 around p50 s.t. n1 <= n2
// if num < n1: pq1.push(num)
// if num > n2: pq2.push(num)
// if n1 <= num <= n2: pq1.push(num)
// while(pq1.size() > pq2.size()+1)  pq2.push(pq1.top()); pq1.pop()
// while(pq2.size() > pq1.size())  pq1.push(pq2.top()); pq2.pop()

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */