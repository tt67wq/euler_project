#ifndef _LeftHeap_H
#define _LeftHeap_H

struct TreeNode;
typedef struct TreeNode *PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(void);
ElementType FindMin(PriorityQueue Q);
int IsEmpty(PriorityQueue Q);
PriorityQueue Merge(PriorityQueue Q1, PriorityQueue Q2);

#define Insert(X, H) (H = Insert1((X), H))
#define DeleteMin(Q) (Q = DeleteMin1(Q))
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);

struct TreeNode {
  ElementType Element;
  PriorityQueue Left;
  PriorityQueue Right;
  int Npl;
};

#endif
