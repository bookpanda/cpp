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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // Dummy node handles the edge case of removing the head seamlessly
        ListNode *dummy = new ListNode(0, head);
        ListNode *fast = dummy;
        ListNode *prev = dummy;
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        while (fast != nullptr) {
            fast = fast->next;
            prev = prev->next;
        }
        ListNode *toBeDeleted = prev->next;
        prev->next = prev->next->next;
        delete toBeDeleted;
        ListNode *newHead = dummy->next;
        delete dummy;

        return newHead;
    }
};

// 0->1
// s     f
// [1,2,3,4,5], n = 2
// 1->2->3->4->5
// s        f
//       s        f
// ALWAYS have to iterate whole list to know size()
// prev->3
// curr->4
// next->5
// prev->next = next
// del curr