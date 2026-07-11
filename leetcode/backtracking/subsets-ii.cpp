#include <algorithm>
#include <unordered_map>
#include <vector>

#define mod1B7 1000000007
class Solution {
  public:
    std::vector<std::vector<int>> subsets;
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
        std::unordered_map<long long, bool> used;
        std::vector<int> subset;

        std::sort(nums.begin(), nums.end());
        genSubsets(nums, 0, subset, used, 0);

        return subsets;
    }
    void genSubsets(std::vector<int> &nums, int idx, std::vector<int> &subset,
                    std::unordered_map<long long, bool> &used, long long hash) {
        // cout << "idx: " << idx << ", [";
        // for (int s : subset) {
        //     cout << s << ",";
        // } cout << "] ";
        // cout << "hash " << hash << "\n";

        if (idx == nums.size()) {
            used[hash] = true;
            subsets.push_back(subset);
            return;
        }

        // 1. take nums[i]
        long long newHash = ((hash * 137) + (11 + nums[idx])) % mod1B7;
        // check duplicate
        if (!used[newHash]) {
            subset.push_back(nums[idx]);
            genSubsets(nums, idx + 1, subset, used, newHash);
            // used[newHash] = false;
            subset.pop_back();
        }

        // 2. not take nums[i]
        genSubsets(nums, idx + 1, subset, used, hash);
    }
};
// [1,2,2], gS(idx,subset,hash)
// gS(0,[],0) -> gS(1,[1],1), gS(1,[],0)
// gS(1,[1],1) -> gS(2,[1,2],139), gS(2,[1],1)
// gS(1,[],0) -> gS(2,[2],2), gS(2,[],0)
// gS(2,[1,2],139) -> gS(3,[1,2,2],139*137+2), gS(3,[1,2],139)
// gS(2,[1],1) -> gS(3,[1,2],139)(SAME HASH, no call), gS(3,[1],1)
// gS(2,[2],2) -> gS(3,[2,2],2*137+2), gS(3,[2],2)
// gS(2,[],0) -> gS(3,[2],2)(SAME HASH), gS(3,[],0)
// 1,2,2 1,2 1 2,2 2 []

// detect duplicate subset
// simplest : used[key] = t/f (must sort nums first)
// key = string representation of subset e.g. [1,2] -> "1,2"
// another way: use hash as key: [1,2]'s key = (1*137 + 2)%(1B+7)

// set of n items -> 2^n subsets
// multiset of n items -> <2^n, at most <2^10