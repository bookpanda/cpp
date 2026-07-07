#include <algorithm>
#include <utility>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> &points, int k) {
        std::vector<std::pair<int, std::vector<int>>> v;
        for (auto point : points) {
            int dist = (point[0] * point[0]) + (point[1] * point[1]);
            v.push_back({dist, point});
        }
        std::sort(v.begin(), v.end());

        std::vector<std::vector<int>> ans;
        for (int i = 0; i < k; i++) {
            ans.push_back(v[i].second);
        }

        return ans;
    }
};