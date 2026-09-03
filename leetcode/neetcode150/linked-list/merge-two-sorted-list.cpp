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
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        ListNode *p1 = list1;
        ListNode *p2 = list2;
        ListNode dummy = ListNode();
        ListNode *curr = &dummy;

        while (p1 && p2) {
            if (p1->val <= p2->val) {
                curr->next = p1;
                p1 = p1->next;
            } else {
                curr->next = p2;
                p2 = p2->next;
            }
            curr = curr->next;
        }
        while (p1) {
            curr->next = p1;
            p1 = p1->next;
            curr = curr->next;
        }
        while (p2) {
            curr->next = p2;
            p2 = p2->next;
            curr = curr->next;
        }

        return dummy.next;
    }
};
// p1->list1, p2->list2
// while(p1 and p2 still have nodes): getting min(p1, p2)
// while(p1 OR p1): just append the rest of the nodes