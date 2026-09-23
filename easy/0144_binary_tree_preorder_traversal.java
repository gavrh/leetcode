// LeetCode 144. Binary Tree Preorder Traversal (Easy)
// https://leetcode.com/problems/binary-tree-preorder-traversal/
// Submitted 2025-04-16 17:00 UTC · runtime N/A · memory 41.6 MB · submission 1608742045

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
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> list = new ArrayList<>();
        preorder(root, list);
        return list;
    }

    public void preorder(TreeNode node, List<Integer> list) {
        if (node == null) {
            return;
        }

        list.add(node.val);

        if (node.left != null) {
            preorder(node.left, list);
        }
        if (node.right != null) {
            preorder(node.right, list);
        }
    }
}
