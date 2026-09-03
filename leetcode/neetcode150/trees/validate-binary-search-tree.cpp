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
    bool isValidBST(TreeNode *root) {
        long long lastValue = LLONG_MIN;
        return inorderTraverse(root, lastValue);
    }
    bool inorderTraverse(TreeNode *node, long long &lastValue) {
        if (node == nullptr)
            return true;

        if (!inorderTraverse(node->left, lastValue))
            return false;
        if (node->val > lastValue) {
            lastValue = node->val;
        } else {
            return false;
        }
        if (!inorderTraverse(node->right, lastValue))
            return false;

        return true;
    }
};
// 1, 2, 3
//

// 1, 5, 3, 4, 6

// in-order traversal: left, self, right