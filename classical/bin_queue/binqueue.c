/*
 * =====================================================================================
 *
 *       Filename:  binqueue.c
 *
 *    Description:  二项队列的实现
 *
 *        Version:  1.0
 *        Created:  2017-12-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "binqueue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* http://m.blog.csdn.net/fktr_70/article/details/50445405 */

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void *checked_malloc(int len) {
  void *p = malloc(len);
  assert(p);
  return p;
}

struct BinNode {
  ElementType Element;
  Position LeftChild;
  Position NextSibling;
};

struct Collection {
  int CurrentSize;
  BinTree TheTrees[MaxTrees];
};

/* 合并两个树 */
BinTree CombineTrees(BinTree t1, BinTree t2) {
  if (t1->Element > t2->Element)
    return CombineTrees(t2, t1);
  t2->NextSibling = t1->LeftChild;
  t1->LeftChild = t2;
  return t1;
}

/* 合并两个森林 */
BinQueue Merge(BinQueue q1, BinQueue q2) {
  BinTree t1, t2, carry = NULL;
  if (q1->CurrentSize + q2->CurrentSize > Capacity) {
    printf("size too big\n");
    exit(EXIT_FAILURE);
  }
  q1->CurrentSize += q2->CurrentSize;

  for (int i = 0, j = 1; j < q1->CurrentSize; i++, j *= 2) {
    t1 = q1->TheTrees[i];
    t2 = q2->TheTrees[i];
    switch (!!t1 + 2 * !!t2 + 4 * !!carry) {
    case 0:
    case 1:
      break;
    case 2:
      q1->TheTrees[i] = t2;
      break;
    case 4:
      q1->TheTrees[i] = carry;
      break;
    case 3:
      carry = CombineTrees(t1, t2);
      q1->TheTrees[i] = q2->TheTrees[i] = NULL;
      break;
    case 5:
      carry = CombineTrees(t1, carry);
      q1->TheTrees[i] = NULL;
      break;
    case 6:
      carry = CombineTrees(t2, carry);
      q2->TheTrees[i] = NULL;
      break;
    case 7:
      q1->TheTrees[i] = carry;
      carry = CombineTrees(t1, t2);
      q2->TheTrees[i] = NULL;
      break;
    }
  }
  return q1;
}

int IsEmpty(BinQueue Q) { return Q->CurrentSize == 0; }

BinQueue Initialize() {
  BinQueue Q = checked_malloc(sizeof(struct Collection));
  Q->CurrentSize = 0;
  return Q;
}

ElementType DeleteMin(BinQueue Q) {
  int i, j;
  int MinTree;
  BinQueue DeletedQueue;
  Position DeletedTree, OldRoot;
  ElementType MinItem;

  if (IsEmpty(Q)) {
    printf("empty heap\n");
    exit(EXIT_FAILURE);
  }

  MinItem = INT_MIN;
  for (i = 0; i < MaxTrees; i++) {
    if (Q->TheTrees[i] && Q->TheTrees[i]->Element < MinItem) {
      MinItem = Q->TheTrees[i]->Element;
      MinTree = i;
    }
  }

  DeletedTree = Q->TheTrees[MinTree];
  OldRoot = DeletedTree;
  DeletedTree = DeletedTree->LeftChild;
  free(OldRoot);
  DeletedQueue = Initialize();
  DeletedQueue->CurrentSize = (1 << MinTree) - 1;
  for (j = MinTree - 1; j >= 0; j--) {
    DeletedQueue->TheTrees[j] = DeletedTree;
    DeletedTree = DeletedTree->NextSibling;
    DeletedQueue->TheTrees[j]->NextSibling = NULL;
  }
  Q->TheTrees[MinTree] = NULL;
  Q->CurrentSize -= DeletedQueue->CurrentSize + 1;
  Merge(Q, DeletedQueue);
  return MinItem;
}
