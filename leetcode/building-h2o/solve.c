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
        pthread_mutex_t *mutex;
        pthread_cond_t *cond;
        int hc;
        int oc;
} H2O;

H2O *h2oCreate() {
        H2O *obj = (H2O *)malloc(sizeof(H2O));
        obj->mutex = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
        obj->cond = (pthread_cond_t *)calloc(1, sizeof(pthread_cond_t));

        // Initialize user defined data here.

        pthread_mutex_init(obj->mutex, NULL);
        pthread_cond_init(obj->cond, NULL);

        obj->hc = 0;
        obj->oc = 0;
        return obj;
}

void hydrogen(H2O *obj) {

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        pthread_mutex_lock(obj->mutex);
        while (obj->hc == 2 && obj->oc == 0) {
                pthread_cond_wait(obj->cond, obj->mutex);
        }
        if (obj->hc == 2 && obj->oc == 1) {
                obj->hc = 0;
                obj->oc = 0;
        }
        releaseHydrogen();
        obj->hc++;
        pthread_mutex_unlock(obj->mutex);
        pthread_cond_signal(obj->cond);
}

void oxygen(H2O *obj) {

        // releaseOxygen() outputs "O". Do not change or remove this line.
        pthread_mutex_lock(obj->mutex);
        while (obj->oc >= obj->hc) {
                pthread_cond_wait(obj->cond, obj->mutex);
        }
        if (obj->hc == 2 && obj->oc == 1) {
                obj->hc = 0;
                obj->oc = 0;
        }
        releaseOxygen();
        obj->oc++;
        pthread_mutex_unlock(obj->mutex);
        pthread_cond_signal(obj->cond);
}

void h2oFree(H2O *obj) {
        // User defined data may be cleaned up here.
        pthread_mutex_destroy(obj->mutex);
        pthread_cond_destroy(obj->cond);
        free(obj);
}
int main() { return 0; }
