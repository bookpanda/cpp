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
#include <climits>

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
    int goodNodes(TreeNode *root) {
        int count = 0;
        traverse(root, INT_MIN, count);

        return count;
    }
    void traverse(TreeNode *node, int maxVal, int &count) {
        if (node == nullptr)
            return;

        int newMaxVal = maxVal;
        if (node->val >= maxVal) {
            count += 1;
            newMaxVal = node->val;
        }

        traverse(node->left, newMaxVal, count);
        traverse(node->right, newMaxVal, count);
    }
};
// func(node, maxVal = max node->val discovered )
// if node->val > maxVal: count += 1, maxVal=node->val