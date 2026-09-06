#include <numeric>
#include <vector>

class Solution {
  private:
    std::vector<int> parent;
    int findParent(int a) {
        if (parent[a] == a)
            return a;
        return parent[a] = findParent(parent[a]);
    }
    bool unionNodes(int a, int b) {
        int rootA = findParent(a);
        int rootB = findParent(b);
        if (rootA == rootB)
            return false;

        parent[rootB] = rootA;
        return true;
    }

  public:
    bool validTree(int n, std::vector<std::vector<int>> &edges) {
        if (edges.size() != n - 1)
            return false;

        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);

        for (const auto &edge : edges) {
            if (!unionNodes(edge[0], edge[1]))
                return false;
        }

        return true;
    }
};
// n nodes, n-1 edges