// LeetCode 94. Binary Tree Inorder Traversal (Easy)
// https://leetcode.com/problems/binary-tree-inorder-traversal/
// Submitted 2025-04-16 16:56 UTC · runtime N/A · memory 41688000 · submission 1608737792

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> list = new ArrayList<>();
        inorder(root, list);
        return list;
    }

    public void inorder(TreeNode node, List<Integer> list) {
        if (node == null) {
            return;
        }
        if (node.left != null) {
            inorder(node.left, list);
        }

        list.add(node.val);

        if (node.right != null) {
            inorder(node.right, list);
        }
    }
}
