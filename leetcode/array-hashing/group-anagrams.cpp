#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs) {
        std::unordered_map<std::string, std::vector<std::string>> anagrams;
        for (const auto &s : strs) {
            std::string key = s; // deep copy
            std::sort(key.begin(), key.end());
            // auto it = anagrams.find(key);
            // if (it == anagrams.end()) {
            //     anagrams[key] = {};
            // }
            // it.push_back(s);
            anagrams[key].push_back(s);
        }

        std::vector<std::vector<std::string>> ans;
        ans.reserve(anagrams.size());
        for (auto &[key, value] : anagrams) {
            ans.push_back(std::move(value)); // eliminate deep copies
            // vectors inside the anagrams map are gutted and left completely empty ({}).
        }
        return ans;
    }
};