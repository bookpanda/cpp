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

#include <vector>

class Solution {
  public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        if (lists.size() == 0)
            return nullptr;
        return mergeLists(lists, 0, lists.size() - 1);
    }
    ListNode *mergeLists(std::vector<ListNode *> &lists, int left, int right) {
        // cout << "mergeLists " << left << ", " << right << "\n";
        if (left == right)
            return lists[left];
        if (right == left + 1)
            return merge2Lists(lists[left], lists[right]);

        int mid = (left + right) / 2;
        ListNode *mergedLeft = mergeLists(lists, left, mid);
        ListNode *mergedRight = mergeLists(lists, mid + 1, right);
        return merge2Lists(mergedLeft, mergedRight);
    }
    ListNode *merge2Lists(ListNode *l1, ListNode *l2) {
        ListNode *dummy = new ListNode();
        ListNode *curr = dummy;

        while (l1 && l2) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                curr = curr->next;
                l1 = l1->next;
            } else {
                curr->next = l2;
                curr = curr->next;
                l2 = l2->next;
            }
        }

        curr->next = (l1 != nullptr) ? l1 : l2;

        ListNode *tmp = dummy->next;
        delete dummy;
        return tmp;
    }
};