/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
        private TreeNode pre = null;
        private Integer min = Integer.MAX_VALUE;

        public int getMinimumDifference(TreeNode root) {
                inOrder(root);
                return min;
        }

        private void inOrder(TreeNode root) {
                if (root == null) {
                        return;
                }
                inOrder(root.left);
                int tmp;

                if (pre != null) {
                        tmp = Math.abs(root.val - pre.val);
                        if (tmp < min) {
                                min = tmp;
                        }
                }
                pre = root;
                inOrder(root.right);
        }
}
