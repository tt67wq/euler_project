#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

static int Height(Position P) {
  if (P == NULL)
    return -1;
  return P->Height;
}

AvlTree MakeEmpty(AvlTree T) {
  if (T == NULL) {
    T = malloc(sizeof(struct AvlNode));
    if (T == NULL) {
      printf("malloc error\n");
      exit(EXIT_FAILURE);
    }
  }
  T->Height = 0;
  T->Left = NULL;
  T->Right = NULL;
  T->Element = 0;
  return T;
}

int GetHeight(AvlTree T) {
  int AL, AR, MAX;
  while (T) {
    AL = GetHeight(T->Left);
    AR = GetHeight(T->Right);
    MAX = (AL > AR) ? AL : AR;
    return MAX + 1;
  }
  return 0;
}

Position Find(ElementType X, AvlTree T) {
  if (T == NULL)
    return NULL;
  if (X < T->Element)
    return Find(X, T->Left);
  else if (X > T->Element)
    return Find(X, T->Right);
  else
    return T;
}

Position FindMin(AvlTree T) {
  if (T == NULL)
    return NULL;
  else if (T->Left == NULL)
    return T;
  return FindMin(T->Left);
}

Position FindMax(AvlTree T) {
  if (T == NULL)
    return NULL;
  else if (T->Right == NULL)
    return T;
  return FindMax(T->Right);
}

void InorderTraversal(AvlTree T) {
  if (T) {
    InorderTraversal(T->Left);
    printf("%d\n", T->Element);
    InorderTraversal(T->Right);
  }
}

void PreorderTraversal(AvlTree T) {
  if (T) {
    printf("%d\n", T->Element);
    PreorderTraversal(T->Left);
    PreorderTraversal(T->Right);
  }
}

void PostorderTraversal(AvlTree T) {
  if (T) {
    PostorderTraversal(T->Left);
    PostorderTraversal(T->Right);
    printf("%d\n", T->Element);
  }
}

void GetOrderPrintLeaves(AvlTree T) {
  if (T) {
    if (T->Left || T->Right) {
      GetOrderPrintLeaves(T->Left);
      GetOrderPrintLeaves(T->Right);
    }
    printf("%d\n", T->Element);
  }
}

int max(int a, int b) { return (a > b) ? a : b; }

// LL型平衡调整，又称单向右旋平衡处理
AvlTree singleLeftRotation(AvlTree T) {
  /* 必须有个左子树 */
  AvlTree LT = T->Left;
  T->Left = LT->Right;
  LT->Right = T;
  T->Height = max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
  LT->Height = max(T->Left, GetHeight(LT->Right)) + 1;

  return LT;
}
