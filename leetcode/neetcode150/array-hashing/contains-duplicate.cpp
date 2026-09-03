#include <unordered_set>
#include <vector>

class Solution {
  public:
    bool containsDuplicate(std::vector<int> &nums) {
        std::unordered_set<int> seen;
        seen.reserve(nums.size()); // prevents rehashs
        for (auto num : nums) {
            // pair: {iterator, bool}. bool is false if element alrdy existed
            if (!seen.insert(num).second) {
                return true;
            }
        }
        return false;
    }
};