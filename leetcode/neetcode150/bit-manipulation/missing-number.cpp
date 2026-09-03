#include <vector>

class Solution {
  public:
    int missingNumber(std::vector<int> &nums) {
        int ans = 0;
        int n = nums.size();          // but nums has numbers in range 0..n (n+1 numbers)
        for (int i = 0; i < n; i++) { // i: 0..n-1 (n numbers)
            ans ^= (i + 1) ^ nums[i];
        }
        // in the end, ans = 1^2^..n ^ (another n numbers in range 0..n)
        // XOR: 0^X=X, A^A=0
        // if missing no. is n, ans = n
        // if mssing no. is n-1, ans = n-1

        return ans;
    }
};
// 0..n, but have n numbers (1 is missing)
// [3,0,1] 11 ^ 00 ^ 01= 10
// [0,1] 1 ^ 0 = 1