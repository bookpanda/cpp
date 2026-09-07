#include <numeric>
#include <vector>

class Solution {
  private:
    std::vector<int> parent;
    int groups;
    int findParent(int a) {
        if (parent[a] == a)
            return a;
        return parent[a] = findParent(parent[a]);
    }
    bool unionParents(int a, int b) {
        int rootA = findParent(a);
        int rootB = findParent(b);
        if (rootA == rootB) { // already same group
            return false;
        }

        parent[rootA] = rootB;
        groups--;
        return true;
    }

  public:
    int countComponents(int n, std::vector<std::vector<int>> &edges) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        groups = n;

        for (const auto &edge : edges) {
            unionParents(edge[0], edge[1]);
        }
        return groups;
    }
};

// parent[node] = node
// if nodes same parent = same group
// initially, n nodes, n groups
// scan each edge (nodes a, b), see if root parent (parent[root]=root) are the same
// if not : union parent: parent[rootA] = parent[rootB] (groups--)
// if same: a, b are already connected in the tree since same root parent
//      if connect this edge again, will create a cycle (groups stay the same)