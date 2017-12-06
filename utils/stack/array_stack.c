/* 栈的数组实现 */

#include "array_stack.h"
#include "apue.h"

Stack CreateStack(int MaxElements) {
  Stack S;
  if (MaxElements < MinStackSize)
    err_sys("Stack size is too small");
  S = malloc(sizeof(struct StackRecord));
  if (S == NULL)
    err_sys("Out of space");
  S->Array = malloc(sizeof(ElementType) * MaxElements);
  if (S->Array == NULL)
    err_sys("Out of space");
  S->Capacity = MaxElements;
  MakeEmpty(S);
  return S;
}

/* 栈的释放 */
void DisposeStack(Stack S) {
  if (S != NULL) {
    free(S->Array);
    free(S);
  }
}

int IsEmpty(Stack S) { return S->TopOfStack == EmptyTOS; }

void MakeEmpty(Stack S) { S->TopOfStack = EmptyTOS; }

void Push(ElementType X, Stack S) {
  if (IsFull(S))
    err_sys("Stack is full");
  else
    S->Array[++S->TopOfStack] = X;
}

ElementType Top(Stack S) {
  if (!IsEmpty(S))
    return S->Array[S->TopOfStack];
  err_sys("Empty stack");
  return 0;
}

void Pop(Stack S) {
  if (IsEmpty(S))
    err_sys("Empty Stack");
  else
    S->TopOfStack--;
}
