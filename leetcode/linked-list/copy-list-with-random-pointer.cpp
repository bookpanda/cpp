/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

#include <unordered_map>

struct Node {
    int val;
    Node *next;
    Node *random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};
class Solution {
  public:
    Node *copyRandomList(Node *head) {
        std::unordered_map<Node *, Node *> node2copy;
        Node *curr = head;
        Node *dummy = new Node(0);
        Node *curr2 = dummy;

        while (curr != nullptr) {
            if (node2copy.find(curr) == node2copy.end()) {
                Node *newNode = new Node(curr->val);
                node2copy[curr] = newNode;
                curr2->next = newNode;
            } else {
                curr2->next = node2copy[curr];
            }
            // cout << "curr " << curr->val << "\n";

            curr2 = curr2->next;

            if (curr->random == nullptr) {
            } else if (node2copy.find(curr->random) == node2copy.end()) {
                Node *newNode = new Node(curr->random->val);
                node2copy[curr->random] = newNode;
                curr2->random = newNode;
            } else {
                curr2->random = node2copy[curr->random];
            }

            curr = curr->next;
        }

        Node *tmp = dummy->next;
        delete dummy;
        return tmp;
    }
};