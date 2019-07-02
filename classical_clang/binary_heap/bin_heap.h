struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;

#define LeftChild(i) (2 * (i) + 1)

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
void HeapSort(ElementType A[], int N);

struct HeapStruct {
        int Capacity;
        int Size;
        ElementType *Elements;
};
