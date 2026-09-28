// LeetCode 102. Binary Tree Level Order Traversal (Medium)
// https://leetcode.com/problems/binary-tree-level-order-traversal/
// Submitted 2026-09-28 05:11 UTC · runtime 0 ms · memory 17 MB · submission 2155585268

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) return {};

        TreeNode* curr;
        queue<TreeNode*> q;
        q.push(root);

        vector<vector<int>> res = {{ root->val }};
        vector<int> next;

        size_t i, n;

        while ((n = q.size()) != 0) {
            next = {};

            for (i = 0; i < n; i++) {
                curr = q.front();

                if (curr->left != nullptr) {
                    q.push(curr->left);
                    next.push_back(curr->left->val);
                }

                if (curr->right != nullptr) {
                    q.push(curr->right);
                    next.push_back(curr->right->val);
                }

                q.pop();
            }

            if (next.size()) res.push_back(next);
        }

        return res;
    }
};
