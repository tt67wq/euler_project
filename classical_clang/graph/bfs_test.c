/*
 * =====================================================================================
 *
 *       Filename:  bfs_test.c
 *
 *    Description:  广度优先搜索的测试
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

int main() {
  int i;
  int count = 0;
  GRAPH G;
  NODE *temp;
  NODE *temp1;
  PTR_NODE *ptr_temp;
  NODEQUEUE Q;

  init_queue(&Q, &G);
  init_graph(&G, 8);

  temp = create_and_init_node(0);
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 1);

  temp = create_and_init_node(1);
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 0);
  insert_to_adj(&G, temp, 2);

  temp = create_and_init_node(2);
  temp1 = temp;
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 1);
  insert_to_adj(&G, temp, 3);

  temp = create_and_init_node(3);
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 2);
  insert_to_adj(&G, temp, 4);
  insert_to_adj(&G, temp, 5);

  temp = create_and_init_node(4);
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 3);
  insert_to_adj(&G, temp, 5);
  insert_to_adj(&G, temp, 6);
  insert_to_adj(&G, temp, 7);

  temp = create_and_init_node(5);
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 3);
  insert_to_adj(&G, temp, 4);
  insert_to_adj(&G, temp, 6);

  temp = create_and_init_node(6);
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 5);
  insert_to_adj(&G, temp, 4);
  insert_to_adj(&G, temp, 7);

  temp = create_and_init_node(7);
  arr_V[count++] = temp;
  insert_to_adj(&G, temp, 6);
  insert_to_adj(&G, temp, 4); //图初始化结束

  for (i = 0; i < 8; i++) {
    ptr_temp = G.adj[i];
    while (ptr_temp != NULL) {
      printf("%d ", ptr_temp->ptr->key);
      ptr_temp = ptr_temp->next;
    }
    printf("\n");
  }
  printf("\n\n");
  BFS(&G, temp1); //执行BFS算法

  for (i = 0; i < count; i++) {
    printf("%d  ", arr_V[i]->d);
  }
  printf("\n");
}
