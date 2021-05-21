/*
 * =====================================================================================
 *
 *       Filename:  dijkstra.c
 *
 *    Description:  戴克斯特拉算法简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define inf 100000
#define V_SIZE 6 // 考虑6个点图的情况

void array_fill(int *array, int len, int val); // 数组填充
void dijkstra(int graph[][V_SIZE], int n, int start, int dist[]);

void array_fill(int *array, int len, int val) {
  int i;
  for (i = 0; i < len; i++) {
    array[i] = val;
  }
}

void dijkstra(int graph[][V_SIZE], int n, int start, int dist[]) {
  int *path = (int *)malloc(sizeof(int) * n);
  int *shortest = (int *)malloc(sizeof(int) * n); // 最短路径数组
  int *mark = (int *)malloc(sizeof(int) * n);
  int min, v, i, j;

  array_fill(mark, n, 0);
  array_fill(dist, n, inf);

  // 找到联通的点
  for (i = 0; i < n; i++) {
    dist[i] = graph[start][i];
    if (i != start && dist[i] < inf) {
      path[i] = start;
    } else {
      path[i] = -1;
    }
  }

  mark[start] = 1; // 标记起始点已经锁定

  while (TRUE) {
    min = inf;
    v = -1;

    for (i = 0; i < n; i++) {
      if (!mark[i]) {
        /* 找到路径最小的联通点 */
        if (dist[i] < min) {
          min = dist[i];
          v = i;
        }
      }
    }
    if (v == -1) {
      /* 找不到最短的路径点 */
      break;
    }
    mark[v] = 1; // 锁定该点
    // 更新dist
    for (i = 0; i < n; i++) {
      if (!mark[i] && graph[v][i] != inf && dist[v] + graph[v][i] < dist[i]) {
        dist[i] = dist[v] + graph[v][i];
        path[i] = v;
      }
    }
  }

  printf("起点\t终点\t最短距离\t对应路径 \n");
  for (i = 0; i < n; i++) {
    if (i == start)
      continue;
    array_fill(shortest, n, 0);
    printf("%d\t", start);
    printf("%d\t", i);
    printf("%d\t", dist[i]);

    int k = 0;
    shortest[k] = i;
    while (path[shortest[k]] != start) {
      k++;
      shortest[k] = path[shortest[k - 1]];
    }
    k++;
    shortest[k] = start;
    for (j = k; j > 0; j--)
      printf("%d->", shortest[j]);
    printf("%d\n", shortest[0]);
  }
  free(path);
  free(shortest);
  free(mark);
  return;
}

int main() {
  int dist[V_SIZE];
  int W[V_SIZE][V_SIZE] = {{0, 1, 4, inf, inf, inf}, {1, 0, 2, 7, 5, inf},
                           {4, 2, 0, inf, 1, inf},   {inf, 7, inf, 0, 3, 2},
                           {inf, 5, 1, 3, 0, 6},     {inf, inf, inf, 2, 6, 0}};

  dijkstra(W, V_SIZE, 2, dist);
  return 0;
}
