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
#include <algorithm>

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
    bool isBalanced(TreeNode *root) {
        bool isBal = true;
        treeDepth(root, isBal);
        return isBal;
    }
    int treeDepth(TreeNode *node, bool &isBal) {
        if (!isBal)
            return 0;
        if (node == nullptr)
            return 0;
        int leftDepth = treeDepth(node->left, isBal);
        int rightDepth = treeDepth(node->right, isBal);
        if (std::abs(leftDepth - rightDepth) > 1) {
            isBal = false;
        }

        return std::max(leftDepth, rightDepth) + 1;
    }
};