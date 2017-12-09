/* 栈的数组实现 */
struct StackRecord;
typedef struct StackRecord *Stack;
typedef char ElementType;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
/* ElementType TopAndPop(Stack S); */

#define EmptyTOS -1
#define MinStackSize 5

struct StackRecord {
  int Capacity;
  int TopOfStack;
  ElementType *Array;
};
