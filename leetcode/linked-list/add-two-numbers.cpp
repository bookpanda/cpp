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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        ListNode *dummy = new ListNode();
        ListNode *head = dummy;
        int carry = 0;

        while (p1 || p2) {
            int sum = carry;
            if (p1 != nullptr) {
                sum += p1->val;
                p1 = p1->next;
            }
            if (p2 != nullptr) {
                sum += p2->val;
                p2 = p2->next;
            }
            carry = sum / 10;
            sum %= 10;
            ListNode *node = new ListNode(sum);
            head->next = node;
            head = node;
        }
        if (carry > 0) {
            ListNode *node = new ListNode(carry);
            head->next = node;
        }

        ListNode *tmp = dummy->next;
        delete dummy;
        return tmp;
    }
};