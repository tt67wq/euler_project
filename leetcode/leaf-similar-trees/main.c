/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-10
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

struct el {
        int val;
        LIST_ENTRY(el) next;
};

LIST_HEAD(list, el);

void getLeafs(struct TreeNode *root, struct list *leafs, int *leafsSize) {
        if (root == NULL) {
                return;
        }
        if (root->left == NULL && root->right == NULL) {
                struct el *leaf = (struct el *)malloc(sizeof(struct el));
                leaf->val = root->val;
                LIST_INSERT_HEAD(leafs, leaf, next);
                (*leafsSize)++;
                return;
        }

        getLeafs(root->left, leafs, leafsSize);
        getLeafs(root->right, leafs, leafsSize);
}

bool leafSimilar(struct TreeNode *root1, struct TreeNode *root2) {
        struct list *leafs1, *leafs2;
        int count1 = 0, count2 = 0;

        leafs1 = (struct list*)malloc(sizeof(struct list));
        leafs2 = (struct list*)malloc(sizeof(struct list));

        LIST_INIT(leafs1);
        LIST_INIT(leafs2);

        getLeafs(root1, leafs1, &count1);
        getLeafs(root2, leafs2, &count2);

        if (count1 != count2) {
                return false;
        }

        while (!LIST_EMPTY(leafs1) && !LIST_EMPTY(leafs2)) {
                if(LIST_FIRST(leafs1)->val == LIST_FIRST(leafs2)->val){
                    LIST_REMOVE(LIST_FIRST(leafs1), next);
                    LIST_REMOVE(LIST_FIRST(leafs2), next);
                }else{
                    return false;
                }
        }
        return true;
}

int main() { return 0; }