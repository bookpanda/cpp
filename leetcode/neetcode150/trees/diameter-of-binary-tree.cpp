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
    int diameterOfBinaryTree(TreeNode *root) {
        int diameter = 0;
        searchTree(root, diameter);
        return diameter;
    }
    int searchTree(TreeNode *node, int &diameter) {
        if (node == nullptr)
            return 0;

        int leftDepth = searchTree(node->left, diameter);
        int rightDepth = searchTree(node->right, diameter);
        int maxPath = leftDepth + rightDepth;
        diameter = std::max(diameter, maxPath);

        return std::max(leftDepth, rightDepth) + 1;
    }
};