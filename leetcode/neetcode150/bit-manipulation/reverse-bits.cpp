class Solution {
  public:
    int reverseBits(int n) {
        int ans;
        for (int i = 0; i < 32; i++) {
            ans <<= 1;
            // cout << "push " << (n & 1) << "\n";
            ans |= (n & 1);
            n >>= 1;
        }
        return ans;
    }
};