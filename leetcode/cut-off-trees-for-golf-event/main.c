/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-10
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 3000
#define DEBUG

typedef struct _pos pos;
struct _pos {
        int row;
        int col;
        int step;
};

void swap(int *a, int *b) {
        int temp;

        temp = *a;
        *a = *b;
        *b = temp;
}

void quick_sort(int *array, int begin, int end) {
        int i, j;
        if (begin < end) {
                i = begin + 1;
                j = end;
                while (i < j) {
                        if (array[i] > array[begin]) {
                                swap(&array[i], &array[j]);
                                j--;
                        } else {
                                i++;
                        }
                }

                if (array[i] >= array[begin])
                        i--;

                swap(&array[begin], &array[i]);
                quick_sort(array, begin, i);
                quick_sort(array, j, end);
        }
}

void clear_queue(void **queue, int front, int rear) {
        for (int i = rear; i != front; i++) {
                free(queue[i]);
                if (i == QUEUE_SIZE) {
                        i = 0;
                }
        }
}

int cutOffTree(int **forest, int forestSize, int *forestColSize) {
        void **queue = (void **)malloc(QUEUE_SIZE * sizeof(void *));
        int front = 0, rear = 0;
        int treeNums = 0;
        int *vis = (int *)calloc(forestSize * forestColSize[0], sizeof(int));
        int *array = (int *)calloc(forestSize * forestColSize[0], sizeof(int));
        for (int i = 0; i < forestSize; i++) {
                for (int j = 0; j < forestColSize[0]; j++) {
                        if (forest[i][j] != 0) {
                                array[treeNums++] = forest[i][j];
                        }
                }
        }
        quick_sort(array, 0, treeNums - 1);

#ifdef DEBUG
        for (int i = 0; i < treeNums; i++) {
                printf("%d ", array[i]);
        }
        printf("\n");
#endif
        int index = 0;
        int counter = 0;
        int ans = 0;
        int flag = 0;

        // push first
        pos *p0 = (pos *)malloc(sizeof(pos));
        p0->row = 0;
        p0->col = 0;
        p0->step = 0;
        queue[front++] = (void *)p0;

        while (1) {
#ifdef DEBUG
                printf("searching for %d\n", array[index]);
#endif
                pos *pt = NULL;
                // search lowest
                while (front != rear) {
                        // pop
                        pt = (pos *)queue[rear++];
                        /* printf("forest[%d][%d] -> %d\n", pt->row, pt->col, */
                        /*        forest[pt->row][pt->col]); */
                        rear = rear >= QUEUE_SIZE ? 0 : rear;

                        if (forest[pt->row][pt->col] == array[index]) {
                                counter++;
                                index++;
                                flag = 1;
                                forest[pt->row][pt->col] = 1;
                                ans += pt->step;
                                bzero(vis, sizeof(int) * forestSize * forestColSize[0]);
                                clear_queue(queue, front, rear);
                                break;
                        }

                        // up
                        if (pt->row > 0 && vis[forestColSize[0] * (pt->row - 1) + pt->col] == 0 &&
                            forest[pt->row - 1][pt->col] > 0) {
                                pos *p1 = (pos *)malloc(sizeof(pos));
                                p1->row = pt->row - 1;
                                p1->col = pt->col;
                                p1->step = pt->step + 1;
                                vis[forestColSize[0] * (pt->row - 1) + pt->col] = 1;
                                queue[front++] = (void *)p1;
                                front = front == QUEUE_SIZE ? 0 : front;
                        }

                        // down
                        if (pt->row + 1 < forestSize &&
                            vis[forestColSize[0] * (pt->row + 1) + pt->col] == 0 &&
                            forest[pt->row + 1][pt->col] > 0) {
                                pos *p2 = (pos *)malloc(sizeof(pos));
                                p2->row = pt->row + 1;
                                p2->col = pt->col;
                                p2->step = pt->step + 1;
                                vis[forestColSize[0] * (pt->row + 1) + pt->col] = 1;
                                queue[front++] = (void *)p2;
                                front = front == QUEUE_SIZE ? 0 : front;
                        }

                        // left
                        if (pt->col > 0 && vis[forestColSize[0] * (pt->row) + pt->col - 1] == 0 &&
                            forest[pt->row][pt->col - 1] > 0) {
                                pos *p3 = (pos *)malloc(sizeof(pos));
                                p3->row = pt->row;
                                p3->col = pt->col - 1;
                                p3->step = pt->step + 1;
                                vis[forestColSize[0] * (pt->row) + pt->col - 1] = 1;
                                queue[front++] = (void *)p3;
                                front = front == QUEUE_SIZE ? 0 : front;
                        }

                        // right
                        if (pt->col + 1 < forestColSize[0] &&
                            vis[forestColSize[0] * (pt->row) + pt->col + 1] == 0 &&
                            forest[pt->row][pt->col + 1] > 0) {
                                pos *p4 = (pos *)malloc(sizeof(pos));
                                p4->row = pt->row;
                                p4->col = pt->col + 1;
                                p4->step = pt->step + 1;
                                vis[forestColSize[0] * (pt->row) + pt->col + 1] = 1;
                                queue[front++] = (void *)p4;
                                front = front == QUEUE_SIZE ? 0 : front;
                        }

                        free(pt);
                }
                if (treeNums == counter) {
                        // clear_queue(queue, front, rear);
                        free(pt);
                        break;
                }

                if (front == rear && flag == 0) {
                        // finded
                        ans = -1;
                        break;
                }

                // push new
                flag = 0;
                front = 0;
                rear = 0;

                pt->step = 0;
                queue[front++] = (void *)pt;
        }
        free(array);
        free(vis);
        free(queue);
        return ans;
}

int main() {
        int r0[] = {1, 2, 3};
        int r1[] = {0, 0, 4};
        int r2[] = {7, 6, 5};

        int *forest[3] = {r0, r1, r2};
        int forestColSize[3] = {3, 3, 3};

        printf("%d\n", cutOffTree(forest, 3, forestColSize));
        return 0;
}
