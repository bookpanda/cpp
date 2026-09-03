/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <climits>
#include <sstream>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Codec {
  public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode *root) {
        if (root == nullptr)
            return ".";

        return std::to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(std::string data) {
        std::vector<int> values;
        std::stringstream ss(data);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (token == ".")
                values.push_back(INT_MIN);
            else
                values.push_back(std::stoi(token));
        }
        // cout << "data " << data << "\n";
        // for (int v : values) {
        //     cout << v << ", ";
        // } cout << "\n";
        int idx = 0;
        return traverse(values, idx);
    }
    TreeNode *traverse(std::vector<int> &values, int &idx) {
        if (values[idx] == INT_MIN) {
            idx++;
            return nullptr;
        }

        TreeNode *node = new TreeNode(values[idx++]);
        // cout << "node " << node->val << "\n";
        node->left = traverse(values, idx);
        node->right = traverse(values, idx);

        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));