/*
 * =====================================================================================
 *
 *       Filename:  image_perimeters.c
 *
 *    Description:  zoj 1047
 *
 *        Version:  1.0
 *        Created:  2019-08-12
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
#define MAX 1000

typedef struct _elem_t {
        int r;
        int c;
} elem_t;

typedef struct _queue {
        int front;
        int rear;
        int size;
        elem_t *buff;
} queue;

int grid[30][30];
int visit[30][30];
int rows, columns, posr, posc;
queue q;

void init(queue *q) {
        q->front = 0;
        q->rear = 0;
        q->size = 0;
        q->buff = (elem_t *)calloc(MAX, sizeof(elem_t));
}

void drop(queue *q) {
        free(q->buff);
        /* free(q); */
}

bool is_full(queue *q) { return q->size == MAX; }
bool is_empty(queue *q) { return q->size == 0; }

bool enqueue(queue *q, elem_t elem) {
        if (is_full(q))
                return false;
        q->buff[q->rear] = elem;
        q->rear = (q->rear + 1) % MAX;
        q->size++;
        return true;
}

bool dequeue(queue *q, elem_t *elem) {
        if (is_empty(q))
                return false;
        *elem = q->buff[q->front];
        q->front = (q->front + 1) % MAX;
        q->size--;
        return true;
}

/* queue finish */

void init_grid() {
        int i, j;
        for (i = 0; i < 20; i++) {
                for (j = 0; j < 20; j++) {
                        grid[i][j] = 0;
                        visit[i][j] = 0;
                }
        }
}

int bfs() {
        elem_t a, b;
        int p = 0;
        int i, j;
        init(&q);

        a.r = posr;
        a.c = posc;
        enqueue(&q, a);
        visit[a.r][a.c] = 1;

        while (dequeue(&q, &b)) {
                if (grid[b.r][b.c - 1] == 0)
                        p++;
                if (grid[b.r][b.c + 1] == 0)
                        p++;
                if (grid[b.r - 1][b.c] == 0)
                        p++;
                if (grid[b.r + 1][b.c] == 0)
                        p++;

                for (i = b.r - 1; i <= b.r + 1; i++) {
                        for (j = b.c - 1; j <= b.c + 1; j++) {
                                if (i <= 0 || i > rows)
                                        continue;
                                if (j <= 0 || j > columns)
                                        continue;
                                if (i == b.r && j == b.c)
                                        continue;
                                if (grid[i][j] == 0)
                                        continue;
                                if (visit[i][j] != 1) {
                                        a.r = i;
                                        a.c = j;
                                        /* printf("入队: grid[%d][%d]\n", i, j); */
                                        visit[i][j] = 1;
                                        enqueue(&q, a);
                                }
                        }
                }
        }
        return p;
}

int main() {
        int i, j;
        char tmp;
        while (1) {
                scanf("%d %d %d %d", &rows, &columns, &posr, &posc);
                if (rows == 0 && columns == 0 && posr == 0 && posc == 0)
                        break;
                init_grid();
                getchar();
                for (i = 1; i <= rows; i++) {
                        for (j = 1; j <= columns; j++) {
                                tmp = getchar();
                                if (tmp == '.')
                                        grid[i][j] = 0;
                                else
                                        grid[i][j] = 1;
                        }
                        getchar();
                }
                printf("%d\n", bfs());
        }
        drop(&q);
        return 0;
}
