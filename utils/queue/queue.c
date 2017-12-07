#include "queue.h"
#include "apue.h"

int IsEmpty(Queue Q) { return Q->Size == 0; }
int IsFull(Queue Q) { return Q->Size == Q->Capacity; }

Queue CreateQueue(int MaxElements) {
  Queue Q;
  if (MaxElements < MinQueueSize)
    err_sys("size too small");
  Q = malloc(sizof(struct QueueRecord));
  if (Q == NULL)
    err_sys("malloc error");
  Q->Array = malloc(sizeof(ElementType) * MaxElements);
  if (Q->Array == NULL)
    err_sys("malloc error");
  MakeEmpty(Q);
  Q->Capacity = MaxElements;
  return Q;
}

void DisposeQueue(Queue Q) {
  if (Q != NULL) {
    free(Q->Array);
    free(Q);
  }
}

void MakeEmpty(Queue Q) {
  Q->Size = 0;
  Q->Front = 1;
  Q->Rear = 0;
}

static int Succ(int Value, Queue Q) {
  if (++Value == Q->Capacity)
    Value = 0;
  return Value;
}

void Enqueue(ElementType X, Queue Q) {
  if (IsFull(Q))
    err_sys("queue is full");
  else {
    Q->Size++;
    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
  }
}

ElementType Front(Queue Q) {
  if (IsEmpty(Q))
    err_sys("empty Queue");
  return Q->Array[Q->Front];
}

void Dequeue(Queue Q) {
  if (IsEmpty(Q))
    err_sys("empty queue");
  Q->Size--;
  Q->Front = Succ(Q->Front, Q);
}
