#include "splay_tree.h"
#include <stdio.h>
#include <stdlib.h>

SplayTree MakeEmpty(SplayTree T) {
  if (!T) {
    T = malloc(sizeof(struct SplayTreeNode));
    if (!T) {
      printf("malloc error\n");
      exit(EXIT_FAILURE);
    }
  }
  T->Element = 0;
  T->Left = T->Right = NULL;
  return T;
}

SplayTree zigRotate(SplayTree T) {
  SplayTree Tmp;
  Tmp = T->Left;
  T->Left = Tmp->Right;
  Tmp->Right = T;
  return Tmp;
}

SplayTree zagRotate(SplayTree T) {
  SplayTree Tmp;
  Tmp = T->Right;
  T->Right = Tmp->Left;
  Tmp->Left = T;
  return Tmp;
}

SplayTree zigzagRotate(SplayTree T) {
  SplayTree Tmp;
  Tmp = zagRotate(T->Left);
  T->Left = Tmp;
  return zigRotate(T);
}

SplayTree zagzigRotate(SplayTree T) {
  SplayTree Tmp;
  Tmp = zigRotate(T->Right);
  T->Right = Tmp;
  return zagRotate(T);
}

SplayTree zigzigRotate(SplayTree T) {
  SplayTree Tmp;
  Tmp = zigRotate(T->Left);
  T->Left = Tmp;
  return zigRotate(T);
}

SplayTree zagzagRotate(SplayTree T) {
  SplayTree Tmp;
  Tmp = zagRotate(T->Right);
  T->Right = Tmp;
  return zagRotate(T);
}

Position Find(ElementType X, SplayTree T) {
  if (!T)
    return NULL;
  while (1) {
    if (X < T->Element) {
      if (!T->Left)
        break;
      if (X < T->Left->Element)
        T = zigzigRotate(T);
      else if (X > T->Left->Element)
        T = zigzagRotate(T);
      else
        T = zigRotate(T);
    } else if (X > T->Element) {
      if (!T->Right)
        break;
      if (X < T->Right->Element)
        T = zagzigRotate(T);
      else if (X > T->Right->Element)
        T = zagzagRotate(T);
      else
        T = zagRotate(T);
    } else {
      //
    }
  }
  if (T->Element == X)
    return T;
  return NULL;
}
