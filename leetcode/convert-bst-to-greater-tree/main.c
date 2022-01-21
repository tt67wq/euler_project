#include <stdio.h>
#include <stdlib.h>

/* 给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum
Tree），使每个节点 node 的新值等于原树中大于或等于node.val的值之和。 */

/* 提醒一下，二叉搜索树满足下列约束条件： */

/* 节点的左子树仅包含键 小于 节点键的节点。 */
/* 节点的右子树仅包含键 大于 节点键的节点。 */
/* 左右子树也必须是二叉搜索树。 */

/* 输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8] */
/* 输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8] */
/* 示例 2： */

/* 输入：root = [0,null,1] */
/* 输出：[1,null,1] */
/* 示例 3： */

/* 输入：root = [1,0,2] */
/* 输出：[3,3,2] */
/* 示例 4： */

/* 输入：root = [3,2,4,1] */
/* 输出：[7,9,4,10] */

/* 来源：力扣（LeetCode） */
/* 链接：https://leetcode-cn.com/problems/convert-bst-to-greater-tree */
/* 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* Definition for a binary tree node. */
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

int convertBSTAndSum(struct TreeNode *root, int base) {
        if (root == NULL)
                return 0;

        int originVal = root->val;

        // leaf
        if (root->left == NULL && root->right == NULL) {
                root->val += base;
                return originVal;
        }

        // left child or right child exists
        int rightSum = convertBSTAndSum(root->right, base);
        root->val += rightSum;
        root->val += base;
        int leftSum = convertBSTAndSum(root->left, root->val);
        /* printf("%d => %d %d\n", originVal, leftSum, rightSum); */

        return leftSum + rightSum + originVal;
}

struct TreeNode *convertBST(struct TreeNode *root) {
        convertBSTAndSum(root, 0);
        return root;
}

int main(int argc, char *argv[]) {
        struct TreeNode n0 = {0, NULL, NULL};
        struct TreeNode n1 = {1, NULL, NULL};
        struct TreeNode n2 = {2, NULL, NULL};
        struct TreeNode n3 = {3, NULL, NULL};
        struct TreeNode n4 = {4, NULL, NULL};
        struct TreeNode n5 = {5, NULL, NULL};
        struct TreeNode n6 = {6, NULL, NULL};
        struct TreeNode n7 = {7, NULL, NULL};
        struct TreeNode n8 = {8, NULL, NULL};

        n1.left = &n0;
        n1.right = &n2;
        n2.right = &n3;
        n4.left = &n1;
        n4.right = &n6;
        n6.left = &n5;
        n6.right = &n7;
        n7.right = &n8;

        struct TreeNode *res = convertBST(&n4);
        printf("%d\n", res->val);

        return 0;
}
