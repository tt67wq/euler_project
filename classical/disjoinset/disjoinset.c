/*
 * =====================================================================================
 *
 *       Filename:  disjoinset.c
 *
 *    Description:  不相交集ADT的实现
 *
 *        Version:  1.0
 *        Created:  2017-12-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
/* http://blog.csdn.net/changyuanchn/article/details/16810535 */
#include "disjoinset.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define OOS (-65536)
#define SIZE (-1)
#define HEIGHT (0)

void *checked_malloc(int len) {
  void *p = malloc(len);
  assert(p);
  return p;
}

void InitializeAsHeight(DisjoinSet gather, const int size) {
  int i;
  gather[0] = size;
  for (i = 0; i <= size; i++)
    gather[i] = HEIGHT;
}

void InitializeAsSize(DisjoinSet gather, const int size) {
  int i;
  gather[0] = size;
  for (i = 0; i <= size; i++)
    gather[i] = SIZE;
}

int SetUnionAsHeight(DisjoinSet gather, SetType root1, SetType root2) {
  if (gather[root1] > 0 || gather[root2] > 0)
    return 0;
  if (gather[root2] < gather[root1])
    gather[root1] = root2;
  else {
    if (gather[root1] == gather[root2]) {
      gather[root1]--;
    }
    gather[root2] = root1;
  }
  return 1;
}

int SetUnionAsSize(DisjoinSet gather, SetType root1, SetType root2) {
  if (gather[root1] > 0 || gather[root2] > 0)
    return 0;
  if (gather[root2] < gather[root1]) {
    gather[root2] += gather[root1];
    gather[root1] = root;
  } else {
    gather[root1] += gather[root2];
    gather[root2] = root1;
  }
  return 1;
}

SetType Find(DisjoinSet gather, const Item item) {
  if (item > gather[0])
    return OOS;
  else if (gather[item] <= 0) {
    return item;
  } else {
    return gather[item] = Find(gather, gather[item]);
  }
}
