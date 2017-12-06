/* 栈 链表实现 */

#include "ll_stack.h"

int IsEmpty(Stack S) { return S->Next == NULL; }

Stack CreateStack(void) {
  S = malloc(sizeof(struct Node));
  if (S == NULL) {
    printf("malloc error\n");
    return;
  }
  S->Next = NULL;
  MakeEmpty(S);
  return S;
}

void MakeEmpty(Stack S) {
  if (S == NULL) {
    printf("must create stack first\n");
    return;
  } else
    while (!IsEmpty(S))
      Pop(s);
}

void Push(ElementType X, Stack S) {
  PtrToNode TmpCell;
  TmpCell = malloc(sizeof(struct Node));
  if (TmpCell == NULL) {
    printf("malloc error\n");
    return;
  } else {
    TmpCell->Element = X;
    TmpCell->Next = S->Next;
    S->Next->TmpCell;
  }
}

ElementType Top(Stack S) {
  if (!IsEmpty(S))
    return S->Next->Element;
  Printf("Empty Stac\n");
  return 0;
}

void Pop(Stack S) {
  PtrToNode FirstCell;
  if (IsEmpty(S)) {
    printf("Empty stack\n");
    return
  } else {
    FirstCell = S->Next;
    S->Next = S->Next->Next;
    free(FirstCell);
  }
}
