/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-04
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

#define GET_MEDIA(small, large, k)                                                                 \
        (((k)&1) ? top((small)) : ((double)top((small)) + (double)top((large))) / 2)

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct _Heap {
        int *heap;
        int heapSize;
        int realSize;
        bool (*cmp)(int, int);
} Heap;

typedef struct _HashTable {
        int key;
        int val;
        UT_hash_handle hh;
} HashTable;

HashTable *hashtable;

void init(Heap *obj, int n, bool (*cmp)(int, int)) {
        obj->heap = malloc(sizeof(int) * (n + 1));
        obj->heap[0] = 0;
        obj->realSize = 0;
        obj->heapSize = 0;
        obj->cmp = cmp;
}

void dispose(Heap *obj) {
        free(obj->heap);
        free(obj);
}

void display(Heap *obj) {
        for (int i = 1; i <= obj->realSize; i++) {
                printf("%d ", obj->heap[i]);
        }
        // printf("%d", top(obj));
        puts("");
}

bool cmp1(int a, int b) { return a < b; }
bool cmp2(int a, int b) { return a > b; }

void swap(int *a, int *b) {
        int c = *a;
        *a = *b, *b = c;
}

void push(Heap *obj, int x) {
        int p = ++(obj->heapSize), q = p >> 1;
        obj->heap[p] = x;
        while (q) {
                if (obj->cmp(obj->heap[q], obj->heap[p])) {
                        swap(&(obj->heap[q]), &(obj->heap[p]));
                        p = q, q = p >> 1;
                } else {
                        break;
                }
        }
}

void pop(Heap *obj) {
        swap(&(obj->heap[1]), &(obj->heap[(obj->heapSize)--]));
        int p = 1, q = p << 1;
        while (q <= obj->heapSize) {
                if (q + 1 <= obj->heapSize) {
                        if (obj->cmp(obj->heap[q], obj->heap[q + 1])) {
                                q++;
                        }
                }
                if (obj->cmp(obj->heap[p], obj->heap[q])) {
                        swap(&(obj->heap[q]), &(obj->heap[p]));
                        p = q, q = p << 1;
                } else {
                        break;
                }
        }
}

int top(Heap *obj) { return obj->heap[1]; }

bool empty(Heap *obj) { return obj->heapSize == 0; }

void prune(Heap *obj) {
        while (!empty(obj)) {
                int num = top(obj);
                HashTable *tmp;
                HASH_FIND_INT(hashtable, &num, tmp);
                if (tmp == NULL) {
                        break;
                }

                tmp->val--;
                if (!(tmp->val)) {
                        HASH_DEL(hashtable, tmp);
                        free(tmp);
                }
                pop(obj);
        }
}

void makeBalance(Heap *small, Heap *large) {
        if (small->realSize > large->realSize + 1) {
                push(large, top(small));
                pop(small);
                --(small->realSize);
                ++(large->realSize);
                prune(small);
        } else if (small->realSize < large->realSize) {
                push(small, top(large));
                pop(large);
                --(large->realSize);
                ++(small->realSize);
                prune(large);
        } else {
                ;
        }
}

void insert(Heap *small, Heap *large, int num) {
        if (empty(small) || num <= top(small)) {
                push(small, num);
                ++(small->realSize);
        } else {
                push(large, num);
                ++(large->realSize);
        }
        makeBalance(small, large);
}

void erase(Heap *small, Heap *large, int num) {
        HashTable *tmp;
        HASH_FIND_INT(hashtable, &num, tmp);

        if (tmp == NULL) {
                tmp = malloc(sizeof(HashTable));
                tmp->key = num;
                tmp->val = 1;
                HASH_ADD_INT(hashtable, key, tmp);
        } else {
                tmp->val++;
        }

        if (num <= top(small)) {
                --(small->realSize);
                if (num == top(small)) {
                        prune(small);
                }
        } else {
                --(large->realSize);
                if (num == top(large)) {
                        prune(large);
                }
        }
        makeBalance(small, large);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double *medianSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
        hashtable = NULL;
        Heap *small, *large;

        small = malloc(sizeof(Heap));
        large = malloc(sizeof(Heap));

        init(small, numsSize, cmp1);
        init(large, numsSize, cmp2);

        for (int i = 0; i < k; i++) {
                // display(small);
                // display(large);
                // puts("----------------------");
                insert(small, large, nums[i]);
        }
        // display(small);
        // display(large);
        // puts("----------------------");

        double *ans = malloc(sizeof(double) * (numsSize - k + 1));
        *returnSize = 0;

        ans[(*returnSize)++] = GET_MEDIA(small, large, k);
        for (int i = k; i < numsSize; i++) {
                // display(small);
                // display(large);
                // puts("----------------------");
                insert(small, large, nums[i]);
                erase(small, large, nums[i - k]);
                ans[(*returnSize)++] = GET_MEDIA(small, large, k);
        }

        dispose(small);
        dispose(large);
        return ans;
}

int main() {
        int nums[] = {5, 2, 2, 7, 3, 7, 9, 0, 2, 3};
        int returnSize;
        double *res = medianSlidingWindow(nums, ARRAY_SIZE(nums), 9, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%0.1f ", res[i]);
        }
        puts("");
        free(res);
        return 0;
}