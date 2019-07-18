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
#define MAX 1000

typedef struct _box {
        int top;
        int right;
        int bottom;
        int left;
        char used;
} box;

int size;
box *boxes;
char *res;

unsigned int js_hash(char *str, unsigned int len) {
        unsigned int hash = 1315423911;
        unsigned int i = 0;

        for (i = 0; i < len; str++, i++) {
                hash ^= ((hash << 5) + (*str) + (hash >> 2));
        }

        return hash;
}

char dfs(char *buff, int index) {
        int i;
        if (index == size * size)
                return 1;
        else if (index == 0) {
                for (i = 0; i < size * size; i++) {
                        buff[0] = i;
                        boxes[i].used = 1;
                        if (dfs(buff, 1))
                                return 1;
                        else {
                                buff[0] = 0;
                                boxes[i].used = 0;
                        }
                }
        } else if (index > 0 && index < size) {
                for (i = 0; i < size * size; i++) {
                        if (boxes[i].used)
                                continue;
                        if (boxes[i].left == boxes[(int)buff[index - 1]].right) {
                                buff[index] = i;
                                boxes[i].used = 1;
                                if (dfs(buff, index + 1))
                                        return 1;
                                else {
                                        buff[index] = 0;
                                        boxes[i].used = 0;
                                }
                        }
                }
        } else if (index % size == 0) {
                for (i = 0; i < size * size; i++) {
                        if (boxes[i].used)
                                continue;
                        if (boxes[i].top == boxes[(int)buff[index - size]].bottom) {
                                buff[index] = i;
                                boxes[i].used = 1;
                                if (dfs(buff, index + 1))
                                        return 1;
                                else {
                                        boxes[i].used = 0;
                                        buff[index] = 0;
                                }
                        }
                }
        } else {
                for (i = 0; i < size * size; i++) {
                        if (boxes[i].used)
                                continue;
                        if ((boxes[i].top == boxes[(int)buff[index - size]].bottom) && (boxes[i].left == boxes[(int)buff[index - 1]].right)) {
                                buff[index] = i;
                                boxes[i].used = 1;
                                if (dfs(buff, index + 1))
                                        return 1;
                                else {
                                        buff[index] = 0;
                                        boxes[i].used = 0;
                                }
                        }
                }
        }
        return 0;
}

int main() {
        int i, j = 0;
        int t, r, b, l;
        char *buff;
        res = (char *)calloc(100, sizeof(char));
        while (scanf("%d", &size) != EOF) {
                if (!size)
                        break;
                boxes = (box *)calloc(size * size, sizeof(box));
                buff = (char *)calloc(size * size, sizeof(char));
                for (i = 0; i < size * size; i++) {
                        scanf("%d %d %d %d", &t, &r, &b, &l);
                        boxes[i].top = t;
                        boxes[i].right = r;
                        boxes[i].bottom = b;
                        boxes[i].left = l;
                        boxes[i].used = 0;
                }
                for (i = 0; i < MAX; i++)
                        ;
                res[j++] = dfs(buff, 0);
                free(boxes);
                free(buff);
        }

        for (i = 0; i < j; i++) {
                if (res[i])
                        printf("Game %d: Possible\n", i + 1);
                else
                        printf("Game %d: Impossible\n", i + 1);
        }
        free(res);
        return 0;
}
