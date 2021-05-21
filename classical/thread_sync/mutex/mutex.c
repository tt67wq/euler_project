/*
 * =====================================================================================
 *
 *       Filename:  mutex.c
 *
 *    Description:  mutex使用
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

pthread_mutex_t mutex;
int N = 10;

void *thread1() {
        // 加锁
        pthread_mutex_lock(&mutex);
        if (N > 0) {
                printf("%d ", N);
                N--;
        }
        pthread_mutex_unlock(&mutex);
        return NULL;
}

int main() {
        int i, num_thread;
        pthread_t *pt;

        num_thread = N;
        pt = (pthread_t *)calloc(num_thread, sizeof(pthread_t));

        // 锁初始化
        pthread_mutex_init(&mutex, NULL);

        for (i = 0; i < num_thread; i++) {
                pthread_create(&pt[i], NULL, thread1, NULL);
        }
        for (i = 0; i < num_thread; i++) {
                pthread_join(pt[i], NULL);
        }
        pthread_mutex_destroy(&mutex);

        return 0;
}
