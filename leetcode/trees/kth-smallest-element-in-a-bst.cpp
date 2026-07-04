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
    int kthSmallest(TreeNode *root, int k) {
        int quota = k;
        int kthSmallest = -1;
        inorderTraverse(root, quota, kthSmallest);
        return kthSmallest;
    }
    void inorderTraverse(TreeNode *node, int &quota, int &kthSmallest) {
        if (node == nullptr || kthSmallest != -1)
            return;

        inorderTraverse(node->left, quota, kthSmallest);
        if (quota == 1) {
            kthSmallest = node->val;
        }
        quota--;
        inorderTraverse(node->right, quota, kthSmallest);
    }
};
// we don't n (no. of nodes)
// need to find n => O(n) -> inorder traversal for k times, then return node->val