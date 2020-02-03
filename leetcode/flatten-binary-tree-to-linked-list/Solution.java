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
        public void flatten(TreeNode root) {
                if (root == null) {
                        return;
                }
                TreeNode tmp;

                flatten(root.left);
                flatten(root.right);

                tmp = root.right;
                root.right = root.left;
                root.left = null;

                // fint leaf
                for (; root.right != null;) {
                        root = root.right;
                }
                root.right = tmp;
        }
}
