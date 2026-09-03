class Solution {
  public:
    int getSum(int a, int b) {
        int carry;
        while (b != 0) { // while there's still carry
            // Cast to unsigned int to avoid undefined behavior on left shift of negative numbers
            carry = (unsigned int)(a & b) << 1; // shift 1 = carry is for the next greater digit
            a = a ^ b;
            b = carry;
        }
        return a;
    }
};