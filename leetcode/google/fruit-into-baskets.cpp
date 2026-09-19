#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    int totalFruit(std::vector<int> &fruits) {
        int n = fruits.size();
        int start = 0;
        int maxLength = 0;
        std::unordered_map<int, int> types;
        for (int i = 0; i < n; i++) {
            if (types.find(fruits[i]) == types.end() && types.size() == 2) {
                // eliminate 1 type, from start
                while (types.size() == 2) {
                    types[fruits[start]]--;
                    if (types[fruits[start]] == 0)
                        types.erase(fruits[start]);
                    start++;
                }
            }

            types[fruits[i]]++;
            // cout << "i="<<i<<", start="<<start<<", "<<"len="<<i-start+1<<"\n";
            maxLength = std::max(maxLength, i - start + 1);
            continue;
        }

        return maxLength;
    }
};
//           0,1,2,3,4,5,6,7,8,9,10
// fruits = [3,3,3,1,2,1,1,2,3,3,4]
// 0-2: types={3}, maxLen=3
// 3: types={1,3}, maxLen=4
// 4: types={1,2}, start=3, maxLen=4
// 5-7: types={1,2}, start=3, maxLen=5

// fruits = [0,1,2,2]

// fruits = [1,2,3,2,2]

// find longest subarray w/ at most 2 types of numbers
// 100k types, pick 2 types
// sliding window , window size = 2 types of fruits

// [1,2,3,2,2]
//. [ ]
//.   [ ] -> ]
// return max length of window