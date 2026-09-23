// LeetCode 2. Add Two Numbers (Medium)
// https://leetcode.com/problems/add-two-numbers/
// Submitted 2025-04-23 13:28 UTC · runtime N/A · memory 77052000 · submission 1615691904

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       ListNode* res = new ListNode(); 
       ListNode* curr = res;

       while (true) {
        if (l1 != nullptr) {
            curr->val += l1->val;
            l1 = l1->next;    
        }
        if (l2 != nullptr) {
            curr->val += l2->val;
            l2 = l2->next;    
        }

        if (curr->val >= 10) {
            curr->val = curr->val % 10;
            curr->next = new ListNode(1);
        }

        if(!l1 && !l2) {
            break;
        }
        curr->next = curr->next ? curr->next : new ListNode();
        curr = curr->next;
       }

       return res;
    }
};
