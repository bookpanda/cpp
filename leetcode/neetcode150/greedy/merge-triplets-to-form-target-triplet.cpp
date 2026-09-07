#include <algorithm>
#include <vector>

class Solution {
  public:
    bool mergeTriplets(std::vector<std::vector<int>> &triplets, std::vector<int> &target) {
        std::vector<int> maxTriplet(3, 0);
        for (const auto &triplet : triplets) {
            if (triplet[0] <= target[0] && triplet[1] <= target[1] && triplet[2] <= target[2]) {
                maxTriplet[0] = std::max(maxTriplet[0], triplet[0]);
                maxTriplet[1] = std::max(maxTriplet[1], triplet[1]);
                maxTriplet[2] = std::max(maxTriplet[2], triplet[2]);
            }
        }

        return maxTriplet == target;
    }
};

// [[2,5,3],[1,8,4],[1,7,5]], target = [2,7,5]
// 2: can take triplet[0/1/2]
// 7: can take triplet[0/2]
// 5: can take triplet[0/1/2]
// for each triplet
//      for i=1..3: check triplet[i]==target[i] && triplet[~i (i=2 -> 1/3) <= target[~i]]
//      add to set

// check each triplet in set, see if they op together to get target or not
// triplets = [[2,5,3],[2,3,4],[1,2,5],[5,2,3]], target = [5,5,5]
// i=1: [5,2,3]
// i=2: [2,5,3]
// i=3: [1,2,5]

// suppose target = [t1,t2,t2] = triplet[a] op triplet[b] op triplet[c]...
// t1 = max(a1,b1,c1...)
// t2 = max(a2,b2,c2...)
// t3 = max(a3,b3,c3...)
// ti only cares about max number (only single number in 1 triplet)
// t1-3 = only care about at most 3 triplets, other triples mean nothing (since take max)