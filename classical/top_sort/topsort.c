/*
 * =====================================================================================
 *
 *       Filename:  topsort.c
 *
 *    Description:  拓扑排序
 *
 *        Version:  1.0
 *        Created:  2017-12-29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
#include "topsort.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int toplogical_sort(PrToLGraph G) {
  int i, j;
  int index = 0;
  int head = 0; // 辅助队列的头
  int rear = 0; // 辅助队列的尾
  int *queue;   // 辅组队列
  int *ins;     // 入度数组char *tops; // 拓扑排序结果数组，记录每个节点的排序后的序号。
        int num = G->vexnum;
        ENode *node;

        ins = (int *)malloc(num * sizeof(int));    /* 入度数组 */
        tops = (char *)malloc(num * sizeof(char)); /* 拓扑排序数组结果 */
        queue = (int *)malloc(num * sizeof(int));  /* 辅助队列 */

        /* 统计每个点的入度 */
        for (i = 0; i < num; i++) {
                node = G->vexs[i]->first_edge;
                while (node != NULL) {
                        ins[node->ivex]++;
                        node = node->next_edge;
                }
        }

        /* 所有入度为0的点入队 */
        for (i = 0; i < num; ++i) {
                if (ins[i] == 0) {
                        queue[rear++] = i;
                }
        }
        while (head != rear) {     /* 队列非空 */
                j = queue[head++]; /* 出列 */
                tops[index++] = G->vexs[j]->data;
                node = G->vexs[j]->first_edge;
                /* 将与node关联的节点的入度-1 */
                /* 若入度为0，则入列 */
                while (node != NULL) {
                        ins[node->ivex]--;
                        if (ins[node->ivex] == 0) {
                                queue[rear++] = node->ivex;
                        } else {
                                // pass
                        }
                        node = node->next_edge;
                }
        }

        if (index != G->vexnum) {
                printf("graph has a cycle\n");
                free(queue);
                free(ins);
                free(tops);
                return 1;
        }

        /* 打印结果 */
        printf("== Topsort: ");
        for (i = 0; i < num; ++i) {
                printf("%c ", tops[i]);
        }
        printf("\n");
        free(queue);
        free(ins);
        free(tops);
        return 1;
}
