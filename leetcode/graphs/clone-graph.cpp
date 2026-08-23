#include <unordered_map>
#include <vector>

// Definition for a Node.
class Node {
  public:
    int val;
    std::vector<Node *> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node *>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node *>();
    }
    Node(int _val, std::vector<Node *> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
  private:
    std::unordered_map<Node *, Node *> copies;

  public:
    Node *cloneGraph(Node *node) {
        if (!node)
            return NULL;

        if (copies.count(node)) {
            return copies[node];
        }

        Node *newNode = new Node(node->val);
        copies[node] = newNode;
        for (Node *neighbor : node->neighbors) {
            newNode->neighbors.push_back(cloneGraph(neighbor));
        }

        return newNode;
    }
};