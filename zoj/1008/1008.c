/*
 * =====================================================================================
 *
 *       Filename:  1008.c
 *
 *    Description:  zoj 1008
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

#include <stdio.h>
#include <stdlib.h>

typedef struct _box {
        int top;
        int right;
        int bottom;
        int left;
        int num;
} box;

int size;
char flag;
box *boxes;

void dfs(char *buff, int total, int index) {
        int i;
        if (index == size * size) {
                flag = 1;
                return;
        }
        if (flag)
                return;

        else if (index == 0) {
                for (i = 0; i < total; i++) {
                        buff[0] = i;
                        boxes[i].num--;
                        dfs(buff, total, 1);
                        buff[0] = 0;
                        boxes[i].num++;
                }
        } else if (index > 0 && index < size) {
                for (i = 0; i < total; i++) {
                        if (!boxes[i].num)
                                continue;
                        if (boxes[i].left == boxes[(int)buff[index - 1]].right) {
                                buff[index] = i;
                                boxes[i].num--;
                                dfs(buff, total, index + 1);
                                buff[index] = 0;
                                boxes[i].num++;
                        }
                }
        } else if (index % size == 0) {
                for (i = 0; i < total; i++) {
                        if (!boxes[i].num)
                                continue;
                        if (boxes[i].top == boxes[(int)buff[index - size]].bottom) {
                                buff[index] = i;
                                boxes[i].num--;
                                dfs(buff, total, index + 1);
                                buff[index] = 0;
                                boxes[i].num++;
                        }
                }
        } else {
                for (i = 0; i < total; i++) {
                        if (!boxes[i].num)
                                continue;
                        if ((boxes[i].top == boxes[(int)buff[index - size]].bottom) && (boxes[i].left == boxes[(int)buff[index - 1]].right)) {
                                buff[index] = i;
                                boxes[i].num--;
                                dfs(buff, total, index + 1);
                                buff[index] = 0;
                                boxes[i].num++;
                        }
                }
        }
}

int main() {
        int i, j, total, k = 1;
        int t, r, b, l;
        char *buff;
        char repeat;
        while (scanf("%d", &size) != EOF) {
                if (!size)
                        break;
                boxes = (box *)calloc(size * size, sizeof(box));
                buff = (char *)calloc(size * size, sizeof(char));
                total = 0;
                for (i = 0; i < size * size; i++) {
                        scanf("%d %d %d %d", &t, &r, &b, &l);
                        repeat = 0;
                        for (j = 0; j < i; j++) {
                                if (boxes[j].top == t && boxes[j].right == r && boxes[j].bottom == b && boxes[j].left == l) {
                                        boxes[j].num += 1;
                                        repeat = 1;
                                        break;
                                }
                        }
                        if (!repeat) {
                                boxes[i].top = t;
                                boxes[i].right = r;
                                boxes[i].bottom = b;
                                boxes[i].left = l;
                                boxes[i].num = 1;
                                total++;
                        }
                }
                flag = 0;
                dfs(buff, total, 0);
                free(boxes);
                free(buff);
                if (k > 1)
                        printf("\n");
                printf("Game %d: ", k++);
                if (flag)
                        printf("Possible\n");
                else
                        printf("Impossible\n");
        }

        return 0;
}
