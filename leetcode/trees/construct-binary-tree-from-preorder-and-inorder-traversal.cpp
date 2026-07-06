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
#include <unordered_map>
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
    TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
        std::unordered_map<int, int> val2InIdx;
        for (int i = 0; i < inorder.size(); i++)
            val2InIdx[inorder[i]] = i;
        int preIdx = 0;

        return build(val2InIdx, preorder, preIdx, 0, inorder.size() - 1);
    }
    TreeNode *build(std::unordered_map<int, int> &val2InIdx, std::vector<int> &preorder, int &preIdx, int inLeft,
                    int inRight) {
        // inOrder[inLeft, inRight]
        if (inLeft > inRight)
            return nullptr;

        int centerVal = preorder[preIdx++];
        int centerInIdx = val2InIdx[centerVal];

        TreeNode *node = new TreeNode(centerVal);
        node->left = build(val2InIdx, preorder, preIdx, inLeft, centerInIdx - 1);
        node->right = build(val2InIdx, preorder, preIdx, centerInIdx + 1, inRight);

        return node;
    }
};