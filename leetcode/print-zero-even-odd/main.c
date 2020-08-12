/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-12
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#define PRINT_NUM(a) printf("%d", (a))

typedef struct {
        int n;
        pthread_mutex_t lock0;
        pthread_mutex_t lock1; // for odd
        pthread_mutex_t lock2; // for even
        bool flag;
} ZeroEvenOdd;

ZeroEvenOdd *zeroEvenOddCreate(int n) {
        ZeroEvenOdd *obj = (ZeroEvenOdd *)malloc(sizeof(ZeroEvenOdd));

        obj->n = n;
        obj->flag = true;
        pthread_mutex_init(&obj->lock0, NULL);
        pthread_mutex_init(&obj->lock1, NULL);
        pthread_mutex_init(&obj->lock2, NULL);

        pthread_mutex_lock(&obj->lock1);
        pthread_mutex_lock(&obj->lock2);

        return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void zero(ZeroEvenOdd *obj) {
        for (int i = 0; i <= obj->n; i++) {
                pthread_mutex_lock(&obj->lock0);
                PRINT_NUM(0);
                if (obj->flag) {
                        pthread_mutex_unlock(&obj->lock1);
                } else {
                        pthread_mutex_unlock(&obj->lock2);
                }
                obj->flag = !obj->flag;
        }
}

void even(ZeroEvenOdd *obj) {
        for (int i = 2; i <= obj->n; i += 2) {
                pthread_mutex_lock(&obj->lock2);
                PRINT_NUM(i);
                pthread_mutex_unlock(&obj->lock0);
        }
}

void odd(ZeroEvenOdd *obj) {
        for (int i = 1; i <= obj->n; i += 2) {
                pthread_mutex_lock(&obj->lock1);
                PRINT_NUM(i);
                pthread_mutex_unlock(&obj->lock0);
        }
}

void zeroEvenOddFree(ZeroEvenOdd *obj) {
    pthread_mutex_destroy(&obj->lock0);
    pthread_mutex_destroy(&obj->lock1);
    pthread_mutex_destroy(&obj->lock2);

    free(obj);
}

int main() { return 0; }