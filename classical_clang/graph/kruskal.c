/*
 * =====================================================================================
 *
 *       Filename:  kruskal.c
 *
 *    Description:  Kruskal最小生成树算法的简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
/* http://blog.csdn.net/luoshixian099/article/details/51908175 */
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define MAXEDGE 10
#define MAXVEX 6

// 边
typedef struct _Edge {
  int start;  // 起点
  int end;    // 终点
  int weight; // 权
} Edge, *PEdge;

// 图
typedef struct _Graph {
  int vexnum;   // 顶点数量
  int edgenum;  // 边数量
  int *vex;     // 顶点集合
  PEdge *edges; // 边集合
} Graph, *PGraph;

int Find(int *parent, int f);
int IsCompeleted(int *paraent);
void Kruskal(PGraph G);

void Kruskal(PGraph G) {
  int i, n, m;
  // 判断边与边之间是否形成环路,元素值parent[i]非0时表示结点i与parent[i]之间的边已确定为生成树的某一条边
  int parent[MAXVEX];
  for (i = 0; i < G->vexnum; ++i)
    parent[i] = -1;

  for (i = 0; i < G->edgenum; ++i) {
    n = Find(parent, G->edges[i]->start);
    m = Find(parent, G->edges[i]->end);
    if (n != m) {
      // 判断边的两个点是否在一个树里面
      parent[n] = m; // 将n与m点连起来printf("(%d, %d) %d\n", G->edges[i]->start, G->edges[i]->end, G->edges[i]->weight);
                }
                if (IsCompeleted(parent)) // 判断是否已经是生成树
                        return;
        }
}

int Find(int *parent, int f) {
        while (parent[f] != -1)
                f = parent[f];
        return f;
}

int IsCompeleted(int *parent) {
        int i;
        int n = 0;
        for (i = 0; i < MAXVEX; ++i) {
                if (parent[i] != -1)
                        ++n;
        }
        if (n == MAXVEX - 1)
                return 1;
        else
                return 0;
}

int main() {
        PGraph G;
        int i, j;
        int t = 0;
        G = malloc(sizeof(Graph));
        G->edgenum = 10;
        G->vexnum = 6;
        G->vex = malloc(sizeof(int) * G->vexnum);
        /* G->edges = malloc(sizeof(Edge) * G->edgenum); */
        for (i = 0; i < G->edgenum; ++i)
                G->edges[i] = malloc(sizeof(Edge));
        printf("初始化图\n");
        for (i = 0; i < G->vexnum; ++i)
                G->vex[i] = i;
        G->edges[0]->start = 0;
        G->edges[0]->end = 2;
        G->edges[0]->weight = 1;

        G->edges[1]->start = 3;
        G->edges[1]->end = 5;
        G->edges[1]->weight = 2;

        G->edges[2]->start = 1;
        G->edges[2]->end = 4;
        G->edges[2]->weight = 3;

        G->edges[3]->start = 2;
        G->edges[3]->end = 5;
        G->edges[3]->weight = 4;

        G->edges[4]->start = 0;
        G->edges[4]->end = 3;
        G->edges[4]->weight = 5;

        G->edges[5]->start = 1;
        G->edges[5]->end = 2;
        G->edges[5]->weight = 5;

        G->edges[6]->start = 2;
        G->edges[6]->end = 4;
        G->edges[6]->weight = 5;

        G->edges[7]->start = 0;
        G->edges[7]->end = 1;
        G->edges[7]->weight = 6;

        G->edges[8]->start = 4;
        G->edges[8]->end = 5;
        G->edges[8]->weight = 6;

        G->edges[9]->start = 2;
        G->edges[9]->end = 3;
        G->edges[9]->weight = 7;
        printf("初始化图完成\n");

        Kruskal(G);
        return 1;
}
