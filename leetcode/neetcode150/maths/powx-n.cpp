#include <cmath>

class Solution {
  public:
    double myPow(double x, int n) {
        if (n == 0 || x == 1.0)
            return 1.0;
        if (x == 0.0)
            return 0.0;

        double product = 1;
        double powX = x;
        long long m = std::abs((long long)n);

        while (m > 0) {
            if (m & 1) {
                product *= powX;
            }
            powX = powX * powX;
            m >>= 1;
        }

        return n < 0 ? 1 / product : product;
    }
};
// x^2 = x*x
// x^4 = x^2*x^2
// n = 1+2+4+8...
// n=5 : 101
// 10(1) : x * 1
// 1(0)1 : x^2 * 0
// (1)01 : x^4 * 1