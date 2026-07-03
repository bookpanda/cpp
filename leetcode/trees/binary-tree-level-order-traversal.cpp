/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
  public:
    std::vector<std::vector<int>> levelOrder(TreeNode *root) {
        std::vector<std::vector<int>> nodes;
        traverseLevel(root, 0, nodes);

        return nodes;
    }
    void traverseLevel(TreeNode *node, int lvl, std::vector<std::vector<int>> &nodes) {
        if (node == nullptr)
            return;

        if (nodes.size() < lvl + 1)
            nodes.resize(lvl + 1);
        nodes[lvl].push_back(node->val);

        traverseLevel(node->left, lvl + 1, nodes);
        traverseLevel(node->right, lvl + 1, nodes);
    }
};