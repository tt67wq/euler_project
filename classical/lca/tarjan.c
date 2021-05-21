/*
 * =====================================================================================
 *
 *       Filename:  tarjan.c
 *
 *    Description:  离线算法求解公共祖先
 *
 *        Version:  1.0
 *        Created:  2019-07-08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

// 参考资料 https://www.cnblogs.com/hulean/p/11144059.html

#include <stdio.h>
#include <stdlib.h>

#define MAX 10
typedef struct btree bt;
struct btree {
        int root;
        bt *left;
        bt *right;
        bt *parent;
};

char path[MAX] = {0};
char vis[MAX] = {0};

void init() {
        for (int i = 1; i < MAX; i++) {
                path[i] = i;
                vis[i] = 0;
        }
}

void create_tree(bt *parent, bt **tree) {
        int ch;
        scanf("%d", &ch);
        if (ch == -1 || ch == 0) {
                // pass
                ;
        } else {
                *tree = (bt *)malloc(sizeof(bt));
                if (*tree == NULL) {
                        printf("failed\n");
                } else {
                        (*tree)->root = ch;
                        (*tree)->parent = parent;
                        printf("输入%d的左子节点：", ch);
                        create_tree(*tree, &((*tree)->left));
                        printf("输入%d的右子节点：", ch);
                        create_tree(*tree, &((*tree)->right));
                }
        }
}

int find(int n) {
        while (path[n] != n) {
                n = path[n];
        }
        return n;
}

void dfs(bt *tree, int (*pair)[3]) {
        if (tree == NULL)
                return;

        if (tree->left != NULL)
                dfs(tree->left, pair);
        if (tree->right != NULL)
                dfs(tree->right, pair);

        int val = tree->root;
        printf("seeking pair for %d\n", val);
        // 寻找关系节点
        for (int i = 0; i < 2; i++) {
                if (pair[i][0] == val) {
                        if (vis[pair[i][1]] == 0) {
                                // pass
                                ;
                        } else {
                                pair[i][2] = find(pair[i][1]);
                        }
                }
                if (pair[i][1] == val) {
                        if (vis[pair[i][0]] == 0) {
                                // pass
                                ;
                        } else {
                                pair[i][2] = find(pair[i][0]);
                        }
                }
        }
        // 返回前一次搜索
        vis[val] = 1;
        if (tree->parent)
                path[val] = tree->parent->root;
}

int main() {
        init();
        int pair[2][3] = {{4, 5, 0}, {5, 3, 0}};
        bt *tree;
        create_tree(NULL, &tree);
        printf("create binary tree finished\n");
        dfs(tree, pair);
        for (int i = 0; i < 2; i++) {
                printf("pair[%d][2] = %d\n", i, pair[i][2]);
        }
        return 0;
}
