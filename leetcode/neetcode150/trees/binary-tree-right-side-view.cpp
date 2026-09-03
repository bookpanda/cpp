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
    std::vector<int> rightSideView(TreeNode *root) {
        std::vector<int> nodes;
        traverseLevel(root, 0, nodes);

        return nodes;
    }
    void traverseLevel(TreeNode *node, int lvl, std::vector<int> &nodes) {
        if (node == nullptr)
            return;

        if (nodes.size() <= lvl) {
            // [], lvl=0 : no node at lvl 0 yet
            // [0], lvl=1 : no node at lvl 1 yet
            nodes.push_back(node->val);
        }
        traverseLevel(node->right, lvl + 1, nodes);
        traverseLevel(node->left, lvl + 1, nodes);
    }
};
// for node to be rightmost of a lvl
// always recurvsive go right before left
// 1st node to be discovered for that lvl = rightmost node for that lvl