/* 符号平衡检测算法，采用栈来实现，读文件直到尾部，遇到开放符合则入栈，遇到闭合符号则出栈
 */

#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

Stack CreateStack(int MaxElements) {
  Stack S;
  if (MaxElements < MinStackSize) {
    puts("Stack size is too small");
    exit(EXIT_FAILURE);
  }

  S = malloc(sizeof(struct StackRecord));
  if (S == NULL) {
    puts("Out of space");
    exit(EXIT_FAILURE);
  }
  S->Array = malloc(sizeof(ElementType) * MaxElements);
  if (S->Array == NULL) {
    puts("Out of space");
    exit(EXIT_FAILURE);
  }
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
int IsFull(Stack S) { return S->TopOfStack == S->Capacity; }

void MakeEmpty(Stack S) { S->TopOfStack = EmptyTOS; }

void Push(ElementType X, Stack S) {
  if (IsFull(S)) {
    puts("Stack is full");
    exit(EXIT_FAILURE);
  } else
    S->Array[++S->TopOfStack] = X;
}

ElementType Top(Stack S) {
  if (!IsEmpty(S))
    return S->Array[S->TopOfStack];
  puts("Empty stack");
  return 0;
}

void Pop(Stack S) {
  if (IsEmpty(S)) {
    puts("Empty Stack");
    exit(EXIT_FAILURE);
  } else
    S->TopOfStack--;
}

int isOpenSymbol(char ch) {
  if (ch == '{' || ch == '[' || ch == '(')
    return TRUE;
  return FALSE;
}

int isCloseSymbol(char ch) {
  if (ch == '}' || ch == ']' || ch == ')')
    return TRUE;
  return FALSE;
}

int main() {
  Stack S;
  char ch;
  S = CreateStack(10);


  while((ch=getchar())!='\n'){
    if (isOpenSymbol(ch)) {
      puts("push one");
      Push(ch, S);
    } else if (isCloseSymbol(ch)) {
      if (IsEmpty(S)) {
        puts("Not Balance");
        return FALSE;
      } else
        Pop(S);
    } else
      continue;
  }
  if (IsEmpty(S)) {
    puts("Balance");
    return TRUE;
  }
  puts("Not Balance In The End");
  return FALSE;
}
