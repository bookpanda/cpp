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
#include <climits>
#include <utility>

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
    int maxPathSum(TreeNode *root) { return findMaxPath(root).first; }
    std::pair<int, int> findMaxPath(TreeNode *node) {
        if (node == nullptr)
            return {-100000, -100000};

        auto [leftMaxPath, leftMaxSimplePath] = findMaxPath(node->left);
        auto [rightMaxPath, rightMaxSimplePath] = findMaxPath(node->right);
        int maxPath = std::max(leftMaxPath, rightMaxPath);
        maxPath = std::max(maxPath, leftMaxSimplePath + node->val);
        maxPath = std::max(maxPath, rightMaxSimplePath + node->val);
        maxPath = std::max(maxPath, leftMaxSimplePath + rightMaxSimplePath + node->val);
        maxPath = std::max(maxPath, node->val); // start new path from node

        int maxSimplePath = std::max(leftMaxSimplePath, rightMaxSimplePath) + node->val;
        maxSimplePath = std::max(maxSimplePath, node->val); // start new simple path from node

        return {maxPath, maxSimplePath};
    }
};