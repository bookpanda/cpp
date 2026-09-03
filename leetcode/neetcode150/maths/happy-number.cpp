#include <unordered_set>

class Solution {
  public:
    bool isHappy(int n) {
        std::unordered_set<int> visited;
        while (1) {
            int sum = 0;
            while (n > 0) {
                int dig = n % 10;
                sum += dig * dig;
                n /= 10;
            }
            n = sum;
            if (n == 1)
                return true;
            if (visited.count(n))
                break;
            visited.insert(n);
        }
        return false;
    }
};
// n =2, sum=4,
// n=4, sum=16
// n=16, sum=37
//