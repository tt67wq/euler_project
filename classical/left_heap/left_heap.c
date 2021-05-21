/*
 * =====================================================================================
 *
 *       Filename:  leaf_heap.c
 *
 *    Description:  左式堆实现
 *
 *        Version:  1.0
 *        Created:  2017-12-21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "left_heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void *checked_malloc(int len) {
  void *p = malloc(len);
  assert(p);
  return p;
}

/*
 *        Name:  Initialize
 * Description:  初始化
 *
 */
PriorityQueue Initialize(void) {
  PriorityQueue Q;
  Q = checked_malloc(sizeof(struct TreeNode));
  Q->Element = 0;
  Q->Left = Q->Right = NULL;
  Q->Npl = 0;
  return Q;
}

/*
 *        Name:  FindMin
 * Description:  寻找最小值
 *
 */
PriorityQueue FindMin(PriorityQueue Q) { return Q->Element; }

/*
 *        Name:  IsEmpty
 * Description:  是否为空
 *
 */
int IsEmpty(PriorityQueue Q) { return Q->Npl == 0; }

/*
 *        Name:  Merge
 * Description:  两个左式堆合并
 *
 */
PriorityQueue Merge(PriorityQueue Q1, PriorityQueue Q2) {
  if (Q1 == NULL)
    return Q2;
  if (Q2 == NULL)
    return Q1;
  if (Q1->Element < Q2->Element)
    return Merge1(Q1, Q2);
  return Merge1(Q2, Q1);
}

static PriorityQueue Merge1(PriorityQueue Q1, PriorityQueue Q2) {
  if (Q1->Left == NULL)
    Q1->Left = Q2;
  else {
    Q1->Right = Merge(Q1->Right, Q2);
    if (Q1->Left->Npl < Q1->Right->Npl)
      SwapChildren(Q1);
    Q1->Npl = Q1->Right->Npl + 1;
  }
  return Q1;
}

/*
 *        Name:  SwapChildren
 * Description:  交换左右子树
 *
 */
void SwapChildren(PriorityQueue Q) {
  PriorityQueue Tmp;
  Tmp = Q->Left;
  Q->Left = Q->Right;
  Q->Right = Tmp;
}

/*
 *        Name:  Insert1
 * Description:  插入一个元素
 *
 */
PriorityQueue Insert1(ElementType X, PriorityQueue Q) {
  PriorityQueue SingleNode;
  SingleNode = Initialize();
  SingleNode->Element = X;
  Q = Merge(SingleNode, Q);
  return Q;
}

/*
 *        Name:  DeleteMin
 * Description:  删除最小元素
 *
 */
PriorityQueue DeleteMin1(PriorityQueue Q) {
  PriorityQueue LeftQ, RightQ;
  if (IsEmpty(Q)) {
    printf("empty heap\n");
    exit(EXIT_FAILURE);
  }
  LeftQ = Q->Left;
  RightQ = Q->Right;
  free(Q);
  return Merge(LeftQ, RightQ);
}
