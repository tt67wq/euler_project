/* ifndef _Double_Queue_H */
/* define _Double_Queue_H */

struct PtrToNode;
typedef struct PtrToNode *DoubleQueue;
typedef int ElementType;

int IsEmpty(DoubleQueue Q);
int IsFull(DoubleQueue Q);
DoubleQueue CreateQueue(void);
void DisposeQueue(DoubleQueue Q);
void MakeEmpty(DoubleQueue Q);
void Push(ElementType X, DoubleQueue Q);
void Pop(DoubleQueue Q);
void Inject(ElementType X, DoubleQueue Q);
void Eject(DoubleQueue Q);
void PrintQueue(DoubleQueue Q);

struct PtrToNode {
        int Front;
        int Rear;
        int Size;
        int Capacity;
        ElementType *Array;
}
