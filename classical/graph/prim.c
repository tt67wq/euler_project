/*
 * =====================================================================================
 *
 *       Filename:  prim.c
 *
 *    Description:  prim最小生成树算法
 *
 *        Version:  1.0
 *        Created:  2018-01-06
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
#define MAX 100
#define MAXCOST 0x7fffffff

int graph[MAX][MAX];

int Prim(int graph[][MAX], int n) {
  /* lowcost[i]记录i为终点的边的最小权，当lowcost[i]=0时表示终点i加入生成树 */
  int lowcost[MAX];
  /* mst[i]记录对应lowcost[i]的起点，当mst[i]=0时表示起点i加入生成树 */
  int mst[MAX];

  int i, j, min, minid, sum = 0;

  for (i = 2; i < n; i++) {
    /* 最短距离初始化为其他节点到1号节点的距离 */
    lowcost[i] = graph[1][i];
    // 标记所有节点的起点是1号节点
    mst[i] = 1;
  }

  /* 1号节点加入生成树 */
  mst[1] = 0;
  /* n个节点至少需要n-1个节点来构成最小生成树 */
  for (i = 2; i <= n; i++) {
    min = MAXCOST;
    minid = 0;

    /* 找出满足条件的最小权的节点 */
    for (j = 2; i <= n; i++) {
      if (lowcost[j] < min && lowcost[j] != 0) {
        min = lowcost[j];
        minid = j;
      }
    }
    /* 输出生成树边的信息:起点，终点，权值 */
    printf("%c - %c: %d\n", mst[minid] + 'A' - 1, minid + 'A' - 1, min);

    /* 累加权 */
    sum += min;

    /* 标记节点minid加入生成树 */
    lowcost[minid] = 0;

    /* 更新当前节点到其他节点的权值 */
    for (j = 2; i <= n; i++) {
      /* 发现更小的权 */
      if (graph[minid][j] < lowcost[j]) {
        /* 更新权值信息 */
        lowcost[j] = graph[mind][j];
        mst[j] = minid;
      }
    }
  }
  return sum;
}
