/*
 * =====================================================================================
 *
 *       Filename:  bin_heap.c
 *
 *    Description:  二叉堆
 *
 *        Version:  1.0
 *        Created:  2019-07-02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "bin_heap.h"
#include <stdio.h>
#include <stdlib.h>

#define MinPQSize 20
#define MinData 0

PriorityQueue Initialize(int MaxElements) {
        PriorityQueue H;

        if (MaxElements < MinPQSize) {
                printf("size too small\n");
                exit(EXIT_FAILURE);
        }
        H = malloc(sizeof(struct HeapStruct));
        if (H == NULL) {
                printf("out of space\n");
                exit(EXIT_FAILURE);
        }
        H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
        if (H->Elements == NULL) {
                printf("out of space\n");
                exit(EXIT_FAILURE);
        }
        H->Capacity = MaxElements;
        H->Size = 0;
        H->Elements[0] = MinData;
        return H;
}

void Destroy(PriorityQueue H) {
        free(H->Elements);
        free(H);
}

void MakeEmpty(PriorityQueue H) {
        if (H == NULL) {
                printf("empty queue\n");
                exit(EXIT_FAILURE);
        }
        H->Capacity = 0;
        H->Size = 0;
        return;
}

void Insert(ElementType X, PriorityQueue H) {
        int i;
        if (IsFull(H)) {
                printf("priority queue if full\n");
                exit(EXIT_FAILURE);
        }
        for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
                H->Elements[i] = H->Elements[i / 2];
        H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H) {
        int i, Child;
        ElementType MinElement, LastElement;

        if (IsEmpty(H)) {
                printf("priority queue if empty\n");
                return H->Elements[0];
        }

        MinElement = H->Elements[1];
        LastElement = H->Elements[H->Size--];

        for (i = 1; i * 2 <= H->Size; i = Child) {
                /* find smaller child */
                Child = i * 2;
                if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
                        Child++;
                /* percolate one level */
                if (LastElement > H->Elements[Child])
                        H->Elements[i] = H->Elements[Child];
                else
                        break;
        }

        H->Elements[i] = LastElement;
        return MinElement;
}

int IsEmpty(PriorityQueue H) { return H->Size == 0; }
int IsFull(PriorityQueue H) { return H->Size == H->Capacity; }

void percDown(ElementType A[], int i, int N) {
        int child;
        ElementType tmp;

        for (tmp = A[i]; LeftChild(i) < N; i = child) {
                child = LeftChild(i);
                if (child != N - 1 && A[child + 1] > A[child])
                        child++;
                if (tmp < A[child])
                        A[i] = A[child];
                else
                        break;
        }
        A[i] = tmp;
}

void swap(int *a, int *b) {
        int tmp = *b;
        *b = *a;
        *a = tmp;
}

/* 堆排序 */
void HeapSort(ElementType A[], int N) {
        int i;
        for (i = N / 2; i >= 0; i--)
                percDown(A, i, N);
        for (i = N - 1; i > 0; i--) {
                swap(&A[0], &A[i]);
                percDown(A, 0, i);
        }
}
