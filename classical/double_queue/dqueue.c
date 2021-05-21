#include "dqueue.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM 20

DoubleQueue CreateQueue() {
        DoubleQueue Q;
        Q = malloc(sizeof(struct PtrToNode));
        if (Q == NULL) {
                puts("malloc queue error\n");
                exit(EXIT_FAILURE);
        }
        Q->Array = malloc(sizeof(ElementType) * NUM);
        if (Q->Array == NULL) {
                puts("malloc queue array error\n");
                free(Q);
                exit(EXIT_FAILURE);
        }
        MakeEmpty(Q);
        return Q;
}

void MakeEmpty(DoubleQueue Q) {
        Q->Size = 0;
        Q->Rear = 0;
        Q->Front = 1;
        Q->Capacity = NUM;
        return;
}

int IsEmpty(DoubleQueue Q) { return Q->Size == 0; }
int IsFull(DoubleQueue Q) { return Q->Size == Q->Capacity; }

void DisposeQueue(DoubleQueue Q) {
        free(Q->Array);
        free(Q);
}

static int RSucc(int X, DoubleQueue Q) {
        if (++X == Q->Capacity)
                X = 0;
        return X;
}
static int FSucc(int X, DoubleQueue Q) {
        if (--X == 0)
                X = Q->Capacity;
        return X;
}

void Push(ElementType X, DoubleQueue Q) {
        if (IsFull(Q)) {
                puts("Queue is full\n");
                exit(EXIT_FAILURE);
        }
        Q->Size++;
        Q->Rear = RSucc(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
}

void Pop(DoubleQueue Q) {
        if (IsEmpty(Q)) {
                puts("Queue is empty\n");
                exit(EXIT_FAILURE);
        }
        Q->Size--;
        Q->Front = RSucc(Q->Front, Q);
}

void Inject(ElementType X, DoubleQueue Q) {
        if (IsFull(Q)) {
                puts("Queue is full\n");
                exit(EXIT_FAILURE);
        }
        Q->Size++;
        Q->Front = FSucc(Q->Front, Q);
        Q->Array[Q->Front] = X;
}

void Eject(DoubleQueue Q) {
        if (IsEmpty(Q)) {
                puts("Queue is empty\n");
                exit(EXIT_FAILURE);
        }
        Q->Size--;
        Q->Rear = FSucc(Q->Rear, Q);
}

void PrintQueue(DoubleQueue Q) {
        if (IsEmpty(Q)) {
                puts("Queue is empty\n");
                exit(EXIT_FAILURE);
        }
        for (i = Q->Rear; i <= Q->Front; i++)
                printf("%d\n", Q->Array[i]);
}
