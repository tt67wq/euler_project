/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  循环队列
 *
 *        Version:  1.0
 *        Created:  2019-07-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct _queue {
        int front;
        int rear;
        int size;
        int *buff;
} queue;

void init(queue *q) {
        q->front = 0;
        q->rear = 0;
        q->size = 0;
        q->buff = (int *)calloc(MAX, sizeof(int));
}

void drop(queue *q) {
        free(q->buff);
        free(q);
}

bool is_full(queue *q) { return q->size == MAX; }
bool is_empty(queue *q) { return q->size == 0; }

bool enqueue(queue *q, int elem) {
        if (is_full(q))
                return false;
        q->buff[q->rear] = elem;
        q->rear = (q->rear + 1) % MAX;
        q->size++;
        return true;
}

bool dequeue(queue *q, int *elem) {
        if (is_empty(q))
                return false;
        *elem = q->buff[q->front];
        q->front = (q->front + 1) % MAX;
        q->size--;
        return true;
}

void print_queue(queue *q) {
        int i;
        i = q->front;
        printf("front -> ");
        while (1) {
                if (i == q->rear)
                        break;
                printf("%d -> ", q->buff[i]);
                i++;
                if (i > MAX)
                        i %= MAX;
        }
        printf("end\n");
}

int main() {
        char *cmd = (char *)calloc(5, sizeof(char));
        queue q;
        int elem;
        init(&q);
        while (scanf("%s", cmd) != EOF) {
                if (!strcmp(cmd, "print")) {
                        print_queue(&q);
                        continue;
                }
                if (!strcmp(cmd, "push")) {
                        scanf("%d", &elem);
                        if (!enqueue(&q, elem))
                                perror("enqueue error");

                        continue;
                }
                if (!strcmp(cmd, "pop")) {
                        if (!dequeue(&q, &elem))
                                perror("dequeue error");
                        continue;
                }
        }
        return 0;
}
