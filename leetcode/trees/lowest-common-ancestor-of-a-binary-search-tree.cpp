/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <algorithm>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
  public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        int small = std::min(p->val, q->val);
        int large = std::max(p->val, q->val);

        TreeNode *node = root;
        while (node != nullptr) {
            if (node->val < small) {
                node = node->right;
            } else if (node->val > large) {
                node = node->left;
            } else if (node->val >= small && node->val <= large)
                break;
        }

        return node;
    }
};
// p!=q (assume p<=q)
// there is node r which p<=r<=q (r could be p or q)
// we're at node n:
// if n < p (out of range): go n->right
// else if n > q (oor): go n->left
// else if p<=n<=q: return n