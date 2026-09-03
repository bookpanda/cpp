#include <climits>
#include <cmath>

class Solution {
  public:
    int reverse(int x) {
        if (x == INT_MIN)
            return 0;
        int n = std::abs(x);
        int rev = 0;

        while (n > 0) {
            if (rev > INT_MAX / 10)
                return 0;
            rev *= 10;
            if (INT_MAX - rev < x % 10)
                return 0;
            rev += n % 10;
            n /= 10;
        }
        // cout << "sign " << sign << "z\n";
        return x < 0 ? -rev : rev;
    }
};