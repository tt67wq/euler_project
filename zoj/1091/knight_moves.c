/*
 * =====================================================================================
 *
 *       Filename:  knight_moves.c
 *
 *    Description:  zoj 1091
 *
 *        Version:  1.0
 *        Created:  2019-08-19
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

#define MAX 10000

typedef struct _pos {
        int row;
        int col;
        int step;
} pos;

typedef struct _queue {
        int front;
        int rear;
        int size;
        pos *buff;
} queue;

pos start;
pos end;
queue pq;
int shifts[16] = {-1, 2, -2, 1, -2, -1, -1, -2, 1, -2, 2, -1, 2, 1, 1, 2};

void init(queue *q) {
        q->front = 0;
        q->rear = 0;
        q->size = 0;
        q->buff = (pos *)calloc(MAX, sizeof(pos));
}

void drop(queue *q) { free(q->buff); }

bool is_full(queue *q) { return q->size == MAX; }
bool is_empty(queue *q) { return q->size == 0; }

bool enqueue(queue *q, pos elem) {
        if (is_full(q))
                return false;
        q->buff[q->rear] = elem;
        q->rear = (q->rear + 1) % MAX;
        q->size++;
        return true;
}

bool dequeue(queue *q, pos *elem) {
        if (is_empty(q))
                return false;
        *elem = q->buff[q->front];
        q->front = (q->front + 1) % MAX;
        q->size--;
        return true;
}

int solve() {
        pos tmp, nxt;
        int i, r, c;
        init(&pq);
        enqueue(&pq, start);
        while (1) {
                dequeue(&pq, &tmp);
                if (tmp.col == end.col && tmp.row == end.row)
                        break;
                for (i = 0; i < 8; i++) {
                        c = shifts[i << 1];
                        r = shifts[(i << 1) + 1];
                        nxt.col = tmp.col + c;
                        nxt.row = tmp.row + r;
                        if (nxt.col < 0 || nxt.col > 7)
                                continue;
                        if (nxt.row < 0 || nxt.row > 7)
                                continue;
                        nxt.step = tmp.step + 1;
                        enqueue(&pq, nxt);
                }
        }

        drop(&pq);
        return tmp.step;
}

int main() {
        while (1) {
                start.col = getchar() - 'a';
                start.row = getchar() - '1';
                start.step = 0;
                getchar();
                end.col = getchar() - 'a';
                end.row = getchar() - '1';
                end.step = 0;
                getchar();
                printf("To get from %c%c to %c%c takes %d knight moves.\n", start.col + 'a', start.row + '1', end.col + 'a', end.row + '1', solve());
        }

        return 0;
}
