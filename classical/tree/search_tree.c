#include "search_tree.h"
#include <stdio.h>
#include <stdlib.h>

void MakeEmpty(SearchTree T) {
  if (T != NULL) {
    MakeEmpty(T->Left);
    MakeEmpty(T->Right);
    free(T);
  }
}

SearchTree CreateTree() {
  SearchTree T;
  T = malloc(sizeof(struct TreeNode));
  if (T == NULL) {
    printf("malloc error\n");
    exit(EXIT_FAILURE);
  }
  /* MakeEmpty(T); */
  int (*CmpFunc)(int, int) = Compare;
  T->Compare = (*CmpFunc);
  T->Left = NULL;
  T->Right = NULL;
  return T;
}

int Compare(ElementType X, ElementType Y) {
  if (X > Y)
    return 1;
  else if (X < Y)
    return -1;
  else
    return 0;
}

Position Find(ElementType X, SearchTree T) {
  if (T == NULL)
    return NULL;
  int cmpr;
  cmpr = T->Compare(X, T->Element);
  if (cmpr == -1)
    return Find(X, T->Left);
  else if (cmpr == 1)
    return Find(X, T->Right);
  else
    return T;
}

Position FindMin(SearchTree T) {
  if (T == NULL)
    return NULL;
  else if (T->Left == NULL)
    return T;
  return FindMin(T->Left);
}

Position FindMax(SearchTree T) {
  if (T == NULL)
    return NULL;
  else if (T->Right == NULL)
    return T;
  return FindMax(T->Right);
}

SearchTree Insert(ElementType X, SearchTree T) {
  if (T == NULL) {
    T = CreateTree();
    T->Element = X;
  } else {
    if (T->Compare(X, T->Element) == -1)
      T->Left = Insert(X, T->Left);
    else if (T->Compare(X, T->Element) == 1)
      T->Right = Insert(X, T->Right);
  }
  return T;
}

int main() {
  SearchTree T;
  T = CreateTree();
  T = Insert(1, T);
  T = Insert(2, T);
  T = Insert(3, T);
  T = Insert(4, T);
  T = Insert(5, T);

  Position Min, Max;
  Min = FindMin(T);
  Max = FindMax(T);
  printf("min: %d\n", Min->Element);
  printf("max: %d\n", Max->Element);

  exit(EXIT_SUCCESS);
}
