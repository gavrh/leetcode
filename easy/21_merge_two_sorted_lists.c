// LeetCode 21. Merge Two Sorted Lists (Easy)
// https://leetcode.com/problems/merge-two-sorted-lists/
// Submitted 2025-03-09 18:51 UTC · runtime N/A · memory 10616000 · submission 1568378645

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <string.h>
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    struct ListNode *head = NULL, **tail = &head;

    while (list1 && list2) {
        if (list1->val < list2->val) {
            *tail = list1;
            list1 = list1->next;
        } else {
            *tail = list2;
            list2 = list2->next;
        }
        tail = &((*tail)->next);
    }
    *tail = list1 ? list1 : list2;
    return head;
}
