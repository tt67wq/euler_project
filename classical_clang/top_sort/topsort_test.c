/*
 * =====================================================================================
 *
 *       Filename:  topsort_test.c
 *
 *    Description:  拓扑排序的测试
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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

/*
 * 返回ch在matrix矩阵中的位置
 */
static int get_position(PrToLGraph g, char ch) {
        int i;
        for (i = 0; i < g->vexnum; i++)
                if (g->vexs[i]->data == ch)
                        return i;
        return -1;
}

/*
 * 将node链接到list的末尾
 */
static void link_last(PENode p, PENode node) {
        while (p->next_edge)
                p = p->next_edge;
        p->next_edge = node;
}

/*
 * 创建邻接表对应的图(用已提供的数据)
 */
LGraph *create_example_lgraph() {
        char c1, c2;
        char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        char edges[][2] = {{'A', 'G'}, {'B', 'A'}, {'B', 'D'}, {'C', 'F'},
                           {'C', 'G'}, {'D', 'E'}, {'D', 'F'}};
        int vlen = LENGTH(vexs);
        int elen = LENGTH(edges);
        int i, p1, p2;
        PENode node1, node2;
        PrToLGraph pG;

        if ((pG = malloc(sizeof(LGraph))) == NULL)
                assert(pG != NULL);
        /* memset(pG, 0, sizeof(LGraph)); */

        // 初始化"顶点数"和"边数"
        printf("初始化顶点数和边数\n");
        pG->vexnum = vlen;
        pG->edgnum = elen;
        pG->vexs = malloc(pG->vexnum * sizeof(PrToVNode));
        for (i = 0; i < pG->vexnum; i++) {
                pG->vexs[i] = malloc(sizeof(VNode));
                pG->vexs[i]->first_edge = malloc(sizeof(ENode));
        }
        /* memset(pG, 0, sizeof(LGraph)); */
        assert(pG->vexs != NULL);
        printf("初始化临近表的顶点\n");
        // 初始化"邻接表"的顶点
        for (i = 0; i < pG->vexnum; i++) {
                pG->vexs[i]->data = vexs[i];
                pG->vexs[i]->first_edge = NULL;
        }

        printf("初始化邻接表的边\n");
        // 初始化"邻接表"的边
        for (i = 0; i < pG->edgnum; i++) {
                // 读取边的起始顶点和结束顶点c1 = edges[i][0];
                c2 = edges[i][1];

                p1 = get_position(pG, c1);
                p2 = get_position(pG, c2);
                printf("p1: %d, p2: %d\n", p1, p2);
                // 初始化node1
                node1 = (ENode *)malloc(sizeof(ENode));
                node1->ivex = p2;
                // 将node1链接到"p1所在链表的末尾"
                if (pG->vexs[p1]->first_edge == NULL) {
                        pG->vexs[p1]->first_edge = node1;
                } else {
                        printf("链接后一个点\n");
                        link_last(pG->vexs[p1]->first_edge, node1);
                }
        }

        return pG;
}

int main() {
        PrToLGraph pG = create_example_lgraph();
        return toplogical_sort(pG);
}
