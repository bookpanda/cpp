/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode *curr = head;
        int i = 0;
        ListNode *dummy = new ListNode(0, head);
        ListNode *prevLast = dummy;
        while (curr != nullptr) {
            i++;
            ListNode *tmp = curr->next;
            if (i == k && k != 1) {
                // swap [prevLast+1, curr]
                prevLast = swapNodes(prevLast, curr);
                i = 0;
                // prevLast = curr;
            }
            curr = tmp;
            // printList(dummy);
        }
        ListNode *newHead = dummy->next;
        delete dummy;
        return newHead;
    }
    ListNode *swapNodes(ListNode *prevLast, ListNode *right) {
        // cout << "swap " << prevLast->val << ", " << right->val << "\n";
        ListNode *prev = prevLast->next;
        prevLast->next = right;
        ListNode *newPrevLast = prev;
        // prevLast = prev;
        // cout << "prevLast now " << prevLast->val << "\n";
        ListNode *curr = prev->next;
        prev->next = right->next;

        while (prev != right) {
            ListNode *tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }
        return newPrevLast;
    }
    void printList(ListNode *head) {
        ListNode *curr = head;
        while (curr != nullptr) {
            std::cout << curr->val << "->";
            curr = curr->next;
        }
        std::cout << "\n";
    }
};
// dummy->1->2->3->(4)
//        p. c  r
// dummy->3->2->1->(4->5->6)

// 5 nodes, k=2 [0,1], [2,3]
// for loop list into a vector, swap idxes, rearrange list : easy