// LeetCode 98. Validate Binary Search Tree (Medium)
// https://leetcode.com/problems/validate-binary-search-tree/
// Submitted 2026-09-28 09:22 UTC · runtime 0 ms · memory 22.5 MB · submission 2155798641

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    struct Bst {
        TreeNode* node;
        long long lo;
        long long hi;
    };

    bool isValidBST(TreeNode* root) {
        size_t n;
        Bst curr;
        Bst top;
        queue<Bst> q;

        top.node = root;
        top.lo = LLONG_MIN;
        top.hi = LLONG_MAX;
        q.push(top);

        while ((n = q.size()) != 0) {
            for (n = n; n > 0; n--) {
                curr = q.front();
                if (curr.node->val <= curr.lo || curr.node->val >= curr.hi) return false;

                if (curr.node->left != nullptr) {
                    if (curr.node->left->val < curr.node->val) {
                        Bst left_cp = curr;

                        left_cp.node = curr.node->left;
                        left_cp.lo = curr.lo;
                        left_cp.hi = min((long long) curr.node->val, left_cp.hi);

                        q.push(left_cp);
                    } else return false;
                }

                if (curr.node->right != nullptr) {
                    if (curr.node->right->val > curr.node->val) {
                        Bst right_cp = curr;

                        right_cp.node = curr.node->right;
                        right_cp.lo = max((long long) curr.node->val, right_cp.lo);

                        q.push(right_cp);
                    } else return false;
                }

                q.pop();
            }
        }
        
        return true;
    }
};
