#include <vector>
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
    void reorderList(ListNode *head) {
        std::vector<ListNode *> nodes;
        ListNode *curr = head;
        while (curr != nullptr) {
            nodes.push_back(curr);
            ListNode *tmp = curr->next;
            curr->next = nullptr;
            curr = tmp;
        }

        int left = 0;
        int right = nodes.size() - 1;
        while (left < right) {
            nodes[left]->next = nodes[right];
            left++;
            if (left >= right)
                break;
            nodes[right]->next = nodes[left];
            right--;
        }
    }
};
// 1->2->3->4->5
// [1,2,3,4,5]
//  l       r
//    l   r

// 1->2
// l. r