#include <limits.h>
#include <vector>

class Solution {
  public:
    int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src, int dst, int k) {
        // bellman-ford
        std::vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        for (int i = 0; i < k + 1; i++) {
            std::vector<int> tmp = dist;
            for (const auto &flight : flights) {
                int from = flight[0], to = flight[1], price = flight[2];
                // use tmp[to] (not dist[to]) to ensure the cheapest finding is never overwritten by sub-optimial path
                // later
                if (dist[from] != INT_MAX && tmp[to] > dist[from] + price) {
                    tmp[to] = dist[from] + price;
                    // cout << "dist["<<to<<"] = from " << from << "(" << dist[from] << ") + " <<price<<"\n";
                }
            }
            dist = std::move(tmp);
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};