// LeetCode 145. Binary Tree Postorder Traversal (Easy)
// https://leetcode.com/problems/binary-tree-postorder-traversal/
// Submitted 2025-04-16 17:06 UTC · runtime 0 ms · memory 42 MB · submission 1608748230

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
    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> list = new ArrayList<>();
        postorder(root, list);
        return list;
    }

    public void postorder(TreeNode node, List<Integer> list) {
        if (node == null) {
            return;
        }
        if (node.left != null) {
            postorder(node.left, list);
        }
        if (node.right != null) {
            postorder(node.right, list);
        }
        list.add(node.val);
    }
}
