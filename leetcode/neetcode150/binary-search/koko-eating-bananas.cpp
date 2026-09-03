#include <vector>

class Solution {
  public:
    int minEatingSpeed(std::vector<int> &piles, int h) {
        int high = piles[0];
        for (int i = 1; i < piles.size(); i++) {
            high = std::max(high, piles[i]);
        }
        int low = 1;
        int minK = high;

        while (low <= high) {
            int k = (high + low) / 2;
            long long time = 0;
            for (int i = 0; i < piles.size(); i++) {
                time += piles[i] / k;
                if (piles[i] % k > 0)
                    time += 1;
            }

            if (time > h) { // eat too slowly
                low = k + 1;
            } else if (time <= h) { // eat fast enough, try decrease speed
                minK = std::min(minK, k);
                high = k - 1;
            }
        }
        return minK;
    }
};
// piles = [30,11,23,4,20], h = 5
// h30, l1, m15: 2+1+2+1+2=8
// h30, l16, m23: 2+1+1+1+1=6
// h30, l24, m27: 2+1+1+1+1=6
// h30, l28, m29 ... = 6
// h30, l30, m30: 1+1+1+1+1 = 5

// piles = [3,6,7,11], h = 8 ,find minimum k
// (3/k)+(6/k)+(7/k)+(11/k) <= 8 (division is ceiled)
// 10k piles, each pile 100M
// O(10k * log(2B)) = O(10K * 32)