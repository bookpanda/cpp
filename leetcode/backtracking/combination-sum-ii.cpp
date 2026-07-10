#include <algorithm>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> ans;
    std::vector<std::vector<int>> combinationSum2(std::vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());

        std::vector<int> selected;
        findCombination(candidates, target, 0, selected, 0);

        return ans;
    }
    void findCombination(std::vector<int> &candidates, int target, int idx, std::vector<int> &selected, int sum) {
        if (sum == target) {
            ans.push_back(selected);
            return;
        }
        if (idx == candidates.size())
            return;

        // 1. take candidates[idx]
        if (sum + candidates[idx] <= target) {
            selected.push_back(candidates[idx]);
            findCombination(candidates, target, idx + 1, selected, sum + candidates[idx]);
            selected.pop_back();
        }

        // 2. skip until candidates[idx+i] > candidates[idx]
        int i = 1;
        while (idx + i < candidates.size()) {
            if (candidates[idx + i] > candidates[idx])
                break;
            i++;
        }
        findCombination(candidates, target, idx + i, selected, sum);
    }
};
// [1,1,2,5,6,7,10], target = 8
// fC(0,[],0) -> fC(1,[1],1), fC(2,[],0)
// fC(1,[1],1) -> fC(2,[1,1],2), fC(2,[1],1)
// fC(2,[],0) -> fC(3,[2],2), fC(3,[],0)
// fC(2,[1,1],2) -> fC(3,[1,1,2],4), fC(3,[1,1],2)
// fC(2,[1],1) -> fC(3,[1,2],3), fC(3,[1],1)

// 1 <= candidates[i] <= 50
// 1 <= target <= 30
// at most 50 candidates to add up to target
// can't do 2^n recursion (too slow) -> need to exit branches early
// worst case [1]*50, target=50
// 1. take candidates[idx]
// 2. skip to candidates[idx+1]
// new 2. skip until candidates[idx+j] > candidates[idx]
// even if we check if(sum <= target), won't help