/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:  氢氧同步
 *
 *        Version:  1.0
 *        Created:  2020-01-18
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
        // User defined data may be declared here.
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        int hc;
        int oc;
} H2O;

H2O *h2oCreate() {
        H2O *obj = (H2O *)malloc(sizeof(H2O));

        // Initialize user defined data here.

        return obj;
}

void hydrogen(H2O *obj) {

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
}

void oxygen(H2O *obj) {

        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
}

void h2oFree(H2O *obj) {
        // User defined data may be cleaned up here.
}
int main() { return 0; }
