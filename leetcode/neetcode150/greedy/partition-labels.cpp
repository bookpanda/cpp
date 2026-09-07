#include <algorithm>
#include <climits>
#include <string>
#include <vector>

class Solution {
  public:
    std::vector<int> partitionLabels(std::string s) {
        std::vector<int> first(26, INT_MAX), last(26, -1);
        for (int i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            first[idx] = std::min(first[idx], i);
            last[idx] = std::max(last[idx], i);
        }

        std::vector<std::pair<int, int>> pairs;
        for (int i = 0; i < 26; i++) {
            if (first[i] == INT_MAX)
                continue;
            pairs.push_back({first[i], last[i]});
        }
        std::sort(pairs.begin(), pairs.end());

        std::vector<int> ans;
        std::pair<int, int> prev = {-1, -1};
        for (int i = 0; i < pairs.size(); i++) {
            if (pairs[i].first < prev.second && pairs[i].second > prev.first) { // overlap
                prev.first = std::min(prev.first, pairs[i].first);
                prev.second = std::max(prev.second, pairs[i].second);
            } else { // disjoint
                // push prev interval to ans first
                if (prev.first != -1)
                    ans.push_back(prev.second - prev.first + 1);

                prev = pairs[i];
            }
        }
        ans.push_back(prev.second - prev.first + 1);

        return ans;
    }
};
// 012345
// ababcc
// for a-z: mark idx of first and last occurence (must be in same partition)
// a: 0,2 | b: 1,3 | c: 4,5 | prev: -1,-1
// a: prev=a
// b: overlap: prev={0,3}
// c: disjoint: push 4 to ans, prev={4,5}
// push 2 to ans

// vector, push [start,end] of each ch
// sort vector by start position -> check adjcent pairs for overlap
// not overlap if A.end < B.start
// overlap if B.start < A.end && B.end > A.start: [A　[B. A]  B]
//      merge: start=min(A.start, B.start), end=max(A.end, B.end)
// c: 4,5