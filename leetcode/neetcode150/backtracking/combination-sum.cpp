#include <algorithm>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> combinations;
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        std::vector<int> selected;
        std::sort(candidates.begin(), candidates.end());

        findCombination(candidates, target, 0, selected, 0);
        return combinations;
    }
    void findCombination(std::vector<int> &candidates, int target, int idx, std::vector<int> &selected, int sum) {
        // cout << "fC(" << idx << "," << sum << ")\n";
        if (sum == target) { // when reach target, early exit
            combinations.push_back(selected);
            return;
        }
        if (idx == candidates.size())
            return;

        // 1. take candidates[idx]
        if (sum + candidates[idx] <= target) {
            selected.push_back(candidates[idx]);
            findCombination(candidates, target, idx, selected, sum + candidates[idx]);
            selected.pop_back();
        }

        // 2. not take, move to candidates[idx+1]
        findCombination(candidates, target, idx + 1, selected, sum);
    }
};
// [2,3,6,7], target=7
// fC(0,[],0) -> fC(1,[2],2), fC(1,[2,2],4), fC(1,[2,2,2],6), fC(1,[],0)
// fC(1,[2],2) -> fC(2,[2,3],5), fC(2,[2],2)
// fC(1,[2,2],4) -> fC(2,[2,2,3],7), fC(2,[2,2],4)
// fC(1,[2,2,2],6) -> fC(2,[2,2,2],6) (don't need, it'll exceed target anyway)
// fC(1,[],0) -> fC(2,[3],3), fC(2,[3,3],6), fC(2,[],0)
// fC(2,[],0) -> fC(3,[6],6), fC(3,[],0)
// fC(3,[],0) -> fC(4,[7],7)

// [2,2,3] [7]

// 2 <= candidates[i] <= 40
// 1 <= target <= 40

// if do recursion: recursion max depth: 40/2 = 20
// itll take maximum of 20 numbers to add up to 40
// 2^10=1024, 2^20=1M