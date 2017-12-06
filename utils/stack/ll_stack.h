/* 栈的链表实现 */

struct Node;
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

struct Node {
  ElementType Element;
  PtrToNode Next;
}
