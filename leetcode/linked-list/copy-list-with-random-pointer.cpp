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

struct Node {
    int val;
    Node *next;
    Node *random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Solution {
  public:
    Node *copyRandomList(Node *head) {
        if (!head)
            return nullptr;

        // 1. copy
        Node *curr = head;
        while (curr != nullptr) {
            Node *newNode = new Node(curr->val);
            newNode->next = curr->next;
            curr->next = newNode;
            curr = newNode->next;
            ;
        }

        // 2. random
        curr = head;
        while (curr != nullptr) {
            if (curr->random != nullptr) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        // 3. unweave
        curr = head;
        Node *newHead = curr->next;
        Node *newCurr = newHead;
        while (curr != nullptr) {
            curr->next = curr->next->next;
            newCurr->next = (newCurr->next != nullptr) ? newCurr->next->next : nullptr;

            curr = curr->next;
            newCurr = newCurr->next;
        }

        return newHead;
    }
};