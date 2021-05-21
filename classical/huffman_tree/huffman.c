/*
 * =====================================================================================
 *
 *       Filename:  huffman.c
 *
 *    Description:  霍夫曼树
 *
 *        Version:  1.0
 *        Created:  2019-07-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* 参考资料：http://data.biancheng.net/view/33.html */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        int weight;              //结点权重
        int parent, left, right; //父结点、左孩子、右孩子在数组中的位置下标
} HTNode, *HuffmanTree;

void select(HuffmanTree ht, int end, int *s1, int *s2) {
        int min1, min2;
        int i = 1, j;

        /* 跳过空节点 */
        while (ht[i].parent && i <= end)
                i++;

        min1 = ht[i].weight;
        *s1 = i;
        i++;

        /* 跳过空节点 */
        while (ht[i].parent && i <= end)
                i++;

        if (ht[i].weight < min1) {
                min2 = min1;
                *s2 = *s1;
                min1 = ht[i].weight;
                *s1 = i;
        } else {
                min2 = ht[i].weight;
                *s2 = i;
        }

        for (j = i + 1; j < end; j++) {
                if (ht[j].parent)
                        continue;
                if (ht[j].weight < min1) {
                        min2 = min1;
                        min1 = ht[j].weight;
                        *s2 = s1;
                        *s1 = j;
                } else if (ht[j].weight > min1 && ht[j].weight < min2) {
                        min2 = ht[j].weight;
                        *s2 = j;
                } else
                        ;
        }
}

void create_huffman(HuffmanTree *ht, int *w, int n) {
        if (n <= 1)
                return;
        int i;
        int m = 2 * n - 1; /* 叶子节点数量 */
        ht = (HuffmanTree *)calloc((m + 1), sizeof(HTNode));

        for (i = 1; i <= n; i++) {
                ht[i]->weight = w[i - 1];
                ht[i]->parent = 0;
                ht[i]->left = 0;
                ht[i]->right = 0;
        }

        /* 从n+1开始初始化霍夫曼树其余节点 */
        for (i = n + 1; i <= m; i++) {
                ht[i]->weight = 0;
                ht[i]->parent = 0;
                ht[i]->left = 0;
                ht[i]->right = 0;
        }

        /* real shit */
        for (i = n + 1; i <= m; i++) {
                int s1, s2;
                select(*ht, i - 1, &s1, &s2);
                ht[s1]->parent = i;
                ht[s2]->parent = i;
                ht[i]->left = s1;
                ht[i]->right = s2;
                ht[i]->weight = ht[s1]->weight + ht[s2]->weight;
        }
}

int main() { return 0; }
