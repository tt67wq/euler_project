/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-29
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

void reverseStr(char *data) {
        int right = strlen(data) - 1;
        int left = 0;
        while (left <= right) {
                char tmp = data[left];
                data[left] = data[right];
                data[right] = tmp;
                left++;
                right--;
        }
}
int cmp(const void *a, const void *b) {
        char *aa = *(char **)a;
        char *bb = *(char **)b;
        return strcmp(aa, bb);
}

void step(struct TreeNode *root, char **res, int *returnSize, int *tmpCounter, char *tmpSave) {
        if (root->left == NULL && root->right == NULL) {
                tmpSave[(*tmpCounter)] =
                    (root->val - 0) +
                    'a'; // 这里不要忘记还要获取一下节点值，这里获取的就是叶子节点值
                (*tmpCounter)++;
                res[(*returnSize)] = (char *)malloc(sizeof(char) * 8500);
                memset(res[*returnSize], 0, sizeof(char) * 8500);
                strncpy(
                    res[*returnSize], tmpSave,
                    (*tmpCounter)); // 这里要使用strncpy,指定拷贝的字符串长度，因为tmpSave相当于全局变量，上一个叶子节点遍历情况可能会影响到当前遍历的情况。
                (*returnSize)++;
                return;
        }
        tmpSave[(*tmpCounter)] = (root->val - 0) + 'a';
        (*tmpCounter)++;
        if (root->left) {
                step(root->left, res, returnSize, tmpCounter, tmpSave);
                (*tmpCounter)--; // 这里一定要，否则tmpsave中存储的就是树的所有节点，而非从跟节点到叶子节点
        }
        if (root->right) {
                step(root->right, res, returnSize, tmpCounter, tmpSave);
                (*tmpCounter)--; // 这里一定要，否则tmpsave中存储的就是树的所有节点，而非从跟节点到叶子节点
        }
}

char *smallestFromLeaf(struct TreeNode *root) {
        if (root == NULL) {
                return NULL;
        }
        char **res = (char **)malloc(sizeof(char *) * 8500);
        int returnSize = 0;
        int tmpCounter = 0;
        char *tmpSave = (char *)malloc(sizeof(char) * 8500);
        memset(tmpSave, 0, sizeof(char) * 8500);
        step(root, res, &returnSize, &tmpCounter, tmpSave);
        for (int i = 0; i < returnSize; i++) {
                // printf("\n11 %s",  res[i]);
                reverseStr(res[i]);
                // printf("\n22 %s",  res[i]);
        }
        qsort(res, returnSize, sizeof(char *), cmp);
#ifdef DEBUG
        printf("\nafter sort:\n");
        for (int k = 0; k < returnSize; k++) {
                printf("%s\n", res[k]);
        }
#endif
        return res[0];
}

int main() {
        struct TreeNode n0;
        struct TreeNode n1;
        struct TreeNode n2;
        struct TreeNode n3;
        struct TreeNode n4;
        struct TreeNode n5;
        struct TreeNode n6;

        n0.val = 0;
        n1.val = 1;
        n2.val = 2;
        n3.val = 3;
        n4.val = 4;
        n5.val = 3;
        n6.val = 4;

        n0.left = &n1;
        n0.right = &n2;

        n1.left = &n3;
        n1.right = &n4;

        n2.left = &n5;
        n2.right = &n6;

        n6.left = NULL;
        n6.right = NULL;

        char *ans = smallestFromLeaf(&n0);
        printf("%s\n", ans);
        free(ans);

        return 0;
}
