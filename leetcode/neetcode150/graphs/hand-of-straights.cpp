#include <queue>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    bool isNStraightHand(std::vector<int> &hand, int groupSize) {
        int n = hand.size();
        if (n % groupSize)
            return false;

        std::priority_queue<int> pq;
        std::unordered_map<int, int> freq;
        for (auto num : hand) {
            pq.push(num);
            freq[num]++;
        }

        while (!pq.empty()) {
            int highest = pq.top();
            pq.pop();
            // cout << "highest " << highest << "\n";
            if (freq[highest] == 0)
                continue;
            for (int i = highest; i > highest - groupSize; i--) {
                if (freq[i] == 0)
                    return false;
                // cout << "take " << i << "\n";
                freq[i]--;
            }
        }
        return true;
    }
};
// [1,2,3,6,2,3,4,7,8]
// 876 [1,2,2,3,3,4]
// 4,3,2 [1,2,3]