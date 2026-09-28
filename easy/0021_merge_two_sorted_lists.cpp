// LeetCode 21. Merge Two Sorted Lists (Easy)
// https://leetcode.com/problems/merge-two-sorted-lists/
// Submitted 2026-09-27 14:57 UTC · runtime 0 ms · memory 19.4 MB · submission 2155071664

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

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr || list2 == nullptr) {
            return list1 == nullptr ? list2 : list1;
        }

        ListNode* res = new ListNode(0);
        ListNode* tail = res;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val == list2->val) {
                tail->next = list1;
                list1 = list1->next;

                tail = tail->next;

                tail->next = list2;
                list2 = list2->next;

                tail = tail->next;
            } else {
                if (list1->val < list2->val) {
                    tail->next = list1;
                    list1 = list1->next;
                } else {
                    tail->next = list2;
                    list2 = list2->next;
                }

                tail = tail->next;
            }
        }

        if (list1 == nullptr) {
            tail->next = list2;
        } else tail->next = list1;

        return res->next;
    }
};
