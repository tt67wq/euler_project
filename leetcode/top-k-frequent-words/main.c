/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-10-28
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
#include <string.h>

typedef struct node {
        char word[20];
        int num;
} NODE;

int cmp1(const NODE *a, const NODE *b) { return (b->num - a->num); }
int cmp2(const NODE *a, const NODE *b) { return strcmp(a->word, b->word); }

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **topKFrequent(char **words, int wordsSize, int k, int *returnSize) {
        NODE *nodes = calloc(wordsSize, sizeof(NODE));
        char **ret = calloc(wordsSize, sizeof(char *));

        int node_idx = 0;

        for (int i = 0; i < wordsSize; i++) {
                bool flag = false;
                for (int j = 0; j < node_idx; j++) {
                        if (strcmp(words[i], nodes[j].word) == 0) {
                                nodes[j].num += 1;
                                flag = true;
                                break;
                        }
                }
                if (!flag) {
                        strcpy(nodes[node_idx].word, words[i]);
                        nodes[node_idx].num = 1;
                        node_idx += 1;
                }
        }

        qsort(nodes, node_idx, sizeof(NODE), cmp2);
        qsort(nodes, node_idx, sizeof(NODE), cmp1);

        for (int i = 0; i < k; i++) {
                ret[i] = nodes[i].word;
        }
        *returnSize = k;
        return ret;
}

int main() { return 0; }