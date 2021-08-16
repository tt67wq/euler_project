// Priority Queue implementation in C

#include <stdio.h>
#include <stdlib.h>

struct heap {
        int size;
        int *array;
};

void swap(int *a, int *b) {
        int temp = *b;
        *b = *a;
        *a = temp;
}

// Function to heapify the tree
void heapify(struct heap *hp, int i) {
        if (hp->size == 1) {
                printf("Single element in the heap");
        } else {
                // Find the largest among root, left child and right child
                int largest = i;
                int l = 2 * i + 1;
                int r = 2 * i + 2;
                if (l < hp->size && hp->array[l] > hp->array[largest])
                        largest = l;
                if (r < hp->size && hp->array[r] > hp->array[largest])
                        largest = r;

                // Swap and continue heapifying if root is not largest
                if (largest != i) {
                        swap(&(hp->array[i]), &(hp->array[largest]));
                        heapify(hp, largest);
                }
        }
}

// Function to insert an element into the tree
void insert(struct heap *hp, int newNum) {
        hp->array[hp->size++] = newNum;
        if (hp->size > 1) {
                for (int i = hp->size / 2 - 1; i >= 0; i--) {
                        heapify(hp, i);
                }
        }
}

// Function to delete an element from the tree
void deleteRoot(struct heap *hp, int num) {
        int i;
        for (i = 0; i < hp->size; i++) {
                if (num == hp->array[i])
                        break;
        }

        swap(&(hp->array[i]), &(hp->array[hp->size - 1]));
        hp->size--;
        for (int i = hp->size / 2 - 1; i >= 0; i--) {
                heapify(hp, i);
        }
}

// Print the array
void printArray(struct heap *hp) {
        for (int i = 0; i < hp->size; ++i)
                printf("%d ", hp->array[i]);
        printf("\n");
}

// Driver code
int main() {
        struct heap *hp = (struct heap *)malloc(sizeof(struct heap));
        hp->array = (int *)calloc(100, sizeof(int));

        insert(hp, 3);
        insert(hp, 4);
        insert(hp, 9);
        insert(hp, 5);
        insert(hp, 2);

        printf("Max-Heap array: ");
        printArray(hp);

        deleteRoot(hp, 4);

        printf("After deleting an element: ");

        printArray(hp);
}