#include <algorithm>
#include <climits>
#include <vector>

class Solution {
  public:
    double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m > n)
            return findMedianSortedArrays(nums2, nums1);

        int high = m, low = 0; // high is m since nums1 could be skipped entirely
        int half = (m + n + 1) / 2;
        while (low <= high) {
            int mid1 = (high + low) / 2;
            int mid2 = half - mid1;
            // assume median of merge is between nums1[mid1] and nums2[mid2];

            int l1 = INT_MIN, r1 = INT_MAX, l2 = INT_MIN, r2 = INT_MAX;
            if (mid1 < m)
                r1 = nums1[mid1];
            if (mid2 < n)
                r2 = nums2[mid2];
            if (mid1 > 0)
                l1 = nums1[mid1 - 1];
            if (mid2 > 0)
                l2 = nums2[mid2 - 1];
            // assume merge looks like: ...xxxx....
            // x could be l1, l2, r1, r2

            // [ {] }, median is between l2, r1
            if (l1 <= r2 && l2 <= r1) {
                if ((m + n) % 2 == 1)
                    return std::max(l1, l2);
                return ((double)(std::max(l1, l2) + std::min(r1, r2))) / 2.0;
            } else if (l1 > r2) {
                high = mid1 - 1;
            } else {
                low = mid1 + 1;
            }
        }
        return 0;
    }
};
// median = merged[(m+n)/2]
//.         v            v
// nums1: aaaA, nums2: bbbBB
// ptr p1,p2 in nums1,nums2 s.t. p1+p2==(m+n)/2
// merged: aaabbbABB

// merged: aabababaabbbababba (sorted)
// aaaababbbb
// l m Lh M H:
// if nums1[m]<=nums2[M]: cut nums1[l..m],nums2[M..H]
// l=m+1, H=M-1

// else: cut nums1[m..h],nums2[L..M]
// h=m-1, L=M+1

// aaabbbbbbbbbb
// bbbbaaaa

// 1,2.     3,4
// l0h1m0   l0h1m0
// l1h1m1.  l0h-1m0