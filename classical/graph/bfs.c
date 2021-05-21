/*
 * =====================================================================================
 *
 *       Filename:  bfs.c
 *
 *    Description:  广度优先算法简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void init_graph(GRAPH *G, int len) {
  /* 初始化图 */
  int i;
  G->length = len;
  for (i = 0; i < len; i++) {
    G->adj[i] = NULL;
  }
}

NODE *create_and_init_node(int key) {
  // 创建和初始化图
  NODE *temp = (NODE *)malloc(sizeof(NODE));
  temp->key = key;
  temp->d = 0;
  temp->f = 0;
  temp->next = NULL;
  temp->parent = NULL;
  return temp;
}

void insert_to_adj(GRAPH *G, NODE *x, int key) {
  // 插入一个点到图
  if (key >= G->length) {
    printf("the key is too big\n");
    return;
  }
  PTR_NODE *temp;
  temp = (PTR_NODE *)malloc(sizeof(PTR_NODE));
  temp->next = G->adj[key];
  temp->ptr = x;
  G->adj[key] = temp;
}

void init_queue(NODEQUEUE *Q, GRAPH *G) {
  // 初始化BFS算法需要用到的队列
  Q->start = 0;
  Q->end = 0;
  Q->length = G->length;
  Q->count = 0;
}

void enqueue(NODEQUEUE *Q, NODE *x) {
  /* 将节点x加入到队列Q中 */
  if (((Q->end + 1) % Q->length) == Q->start)
    return;
  else {
    Q->arr_temp[Q->end++] = x;
    if (Q->end == Q->length)
      Q->end = 0;
    Q->count++;
  }
}

NODE *dequeue(NODEQUEUE *Q) {
  /* 返回Q->arr[Q->start]，同时将这个数组给删除。同时，Q->count减1。 */
  NODE *temp;
  if (Q->start == Q->end)
    return NULL;
  else {
    temp = Q->arr_temp[Q->start++];
    if (Q->start == Q->length)
      Q->start = 0;
    Q->count--;
  }
  return temp;
}

void BFS(GRAPH *G, NODE *s) {
  /* 先探索和当前节点邻接的顶点，然后再探索别的点 */
  int i;
  NODEQUEUE Q;
  init_queue(&Q, G);
  NODE *temp;
  PTR_NODE *ptr_temp;

  for (i = 0; i < G->length; i++) {
    if (arr_V[i] != s) {
      arr_V[i]->color = WHITE;
      arr_V[i]->d = INFINITE;
      arr_V[i]->parent = NULL;
    }
  }

  s->color = GRAY;
  s->parent = NULL;
  s->d = 0;
  enqueue(&Q, s);

  while (Q.count != 0) {
    temp = dequeue(&Q);
    ptr_temp = G->adj[temp->key];
    while (ptr_temp != NULL) {
      if (ptr_temp->ptr->color == WHITE) {
        ptr_temp->ptr->color = GRAY;
        ptr_temp->ptr->d = temp->d + 1;
        ptr_temp->ptr->parent = temp;
        enqueue(&Q, ptr_temp->ptr);
      }
      ptr_temp = ptr_temp->next;
    }
    temp->color = BLACK;
  }
}
