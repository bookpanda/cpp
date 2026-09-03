class Solution {
  public:
    int hammingWeight(int n) {
        int count = 0;
        while (n > 0) {
            count += n & 1;
            n >>= 1;
        }

        return count;
    }
};
// 11 = 1011
// c=1, 101
// c=2, 10
// c=2, 1
// c3, 0