// LeetCode 104. Maximum Depth of Binary Tree (Easy)
// https://leetcode.com/problems/maximum-depth-of-binary-tree/
// Submitted 2026-09-28 04:53 UTC · runtime 0 ms · memory 22.2 MB · submission 2155567700

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
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;

        queue<TreeNode*> q;
        q.push(root);

        TreeNode* curr;
        size_t i, n, m {};

        while (q.size() != 0) {
            n = q.size();
            for (i = 0; i < n; i++) {
                curr = q.front();

                if (curr->left != nullptr) {
                    q.push(curr->left);
                }

                if (curr->right != nullptr) {
                    q.push(curr->right);
                }

                q.pop();
            }

            m++;
        }

        return m;
    }
};
