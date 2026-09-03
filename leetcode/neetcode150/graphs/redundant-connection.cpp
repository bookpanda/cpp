#include <numeric>
#include <vector>

class Solution {
  private:
    std::vector<int> parent;
    std::vector<int> rank;
    int findParent(int a) {
        if (parent[a] == a)
            return a;
        return parent[a] = findParent(parent[a]); // path compression
    }
    bool unionNodes(int a, int b) {
        int rootA = findParent(a);
        int rootB = findParent(b);

        if (rootA == rootB)
            return false; // CYCLE

        // union by rank
        if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        } else if (rank[rootB] < rank[rootA]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }

        return true;
    }

  public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>> &edges) {
        // n == edges.length
        int n = edges.size();
        parent.resize(n + 1);
        // parent[i] = i
        std::iota(parent.begin(), parent.end(), 0);
        rank.assign(n + 1, 0);

        for (const auto &edge : edges) {
            if (!unionNodes(edge[0], edge[1])) {
                return edge;
            }
        }

        // std::unreachable();
        return {};
    }
};
// 1-5-3-4-2
// 4-5
// tree n nodes has n-1 edges
// with one additional edge added -> n edges -> 1 cycle
//  edge that can be removed = any edge in the cycle

// union find
// every node starts by having parent[node] = node
// edge (a, b)
// if (parent[b] != parent[a])
// union node b to a; parent[b] = a
// else
//  a, b are already connected, so this edge is redudundant (CYCLE) -> return early