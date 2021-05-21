/*
 * =====================================================================================
 *
 *       Filename:  dfs.c
 *
 *    Description:  深度优先搜索简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

/* http://blog.csdn.net/qq_39630587/article/details/77448530 */
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define MAXVERTICES 100
#define MAX_VERTEX_NUM 10

typedef struct node {
  int adjvex;
  struct node *next;
} EdgeNode;

typedef struct {
  int vertex;
  EdgeNode *edgenext;
} VertexNode;

typedef VertexNode AdjList[MAXVERTICES];

typedef struct {
  AdjList adjlist;
  int n, e;
} AdjMatrix;

int visited[MAX_VERTEX_NUM];

void CreateGraph(AdjMatrix *G);
void DispGraph(AdjMatrix *G);
void DFS(AdjMatrix *G, int v);
void DFSTraverse(AdjMatrix *G);

int main() {
  freopen("data.txt", "r", stdin);
  AdjMatrix *mx = (AdjMatrix *)malloc(sizeof(AdjMatrix));
  CreateGraph(mx);
  DFSTraverse(mx);
  DispGraph(mx);
  return 0;
}

void CreateGraph(AdjMatrix *G) {
  int i, j, k, w, v;
  EdgeNode *s;
  printf("输入顶点数和边数目: \n");
  scanf("%d%d", &G->n, &G->e);
  printf("建立顶点列表\n");

  for (i = 0; i < G->n; ++i) {
    getchar();
    printf("请输入第%d个顶点的信息: \n", i + 1);
    G->adjlist[i].vertex = getchar();
    G->adjlist[i].edgenext = NULL;
  }

  printf("建立边表\n");
  for (k = 0; k < G->e; ++k) {
    printf("输入有链接的顶点序号\n");
    scanf("%d%d", &i, &j);
    i -= 1;
    j -= 1;
    s = (EdgeNode *)malloc(sizeof(EdgeNode));
    s->adjvex = j;
    s->next = G->adjlist[i].edgenext;
    G->adjlist[i].edgenext = s;

    s = (EdgeNode *)malloc(sizeof(EdgeNode));
    s->adjvex = i;
    s->next = G->adjlist[j].edgenext;
    G->adjlist[j].edgenext = s;
  }
}

void DispGraph(AdjMatrix *G) {
  int i;
  for (i = 0; i < G->n; ++i) {
    printf("%d->", i + 1);
    while (1) {
      if (G->adjlist[i].edgenext == NULL) {
        printf("^");
        break;
      } else {
        printf("%d->", G->adjlist[i].edgenext->adjvex + 1);
        G->adjlist[i].edgenext = G->adjlist[i].edgenext->next;
      }
    }
    printf("\n");
  }
}

void DFS(AdjMatrix *G, int v) {
  EdgeNode *p;
  printf("在%d点进行深度搜索\n", v+1);
  printf("->%c", G->adjlist[v].vertex);
  visited[v] = 1;
  p = G->adjlist[v].edgenext;
  while (p) {
    if (!visited[p->adjvex]) {
      DFS(G, p->adjvex);
    }
    p = p->next;
  }
}

void DFSTraverse(AdjMatrix *G) {
  printf("深度优先搜索顺序: ");
  for (int v = 0; v < G->n; ++v) {
    visited[v] = 0;
  }
  for (int v = 0; v < G->n; ++v) {
    if (!visited[v])
      DFS(G, v);
  }
  printf("\n\n");
}
