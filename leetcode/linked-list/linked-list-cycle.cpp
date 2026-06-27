/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
  public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr)
            return false;

        ListNode *p1 = head;
        ListNode *p2 = head->next;

        while (p1 && p2) {
            if (p1 == p2)
                return true;
            p1 = p1->next;
            if (p2->next)
                p2 = p2->next->next;
            else
                return false;
        }

        return false;
    }
};
// circular race track length: 12m
// runnerA: 3m/s, runnerB: 4 m/s
// when would they meet?: 12m, 24, 36.. (LCM)

// 3->2->0->-4->(2)
// p1: 1node/loop, p2: 2nodes/loop
// if there's loop: p1, p2 will eventually meet again