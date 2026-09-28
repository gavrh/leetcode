// LeetCode 141. Linked List Cycle (Easy)
// https://leetcode.com/problems/linked-list-cycle/
// Submitted 2026-09-28 04:24 UTC · runtime 4 ms · memory 11.8 MB · submission 2155542382

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr) return false;

        ListNode* j = head;

        while (j->next != nullptr) {
            j = j->next;

            if (j->next != nullptr) {
                j = j->next;
            } else break;

            if (head == j) return true;

            head = head->next;
        }

        return false;
    }
};
