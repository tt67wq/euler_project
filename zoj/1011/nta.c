/*
 * =====================================================================================
 *
 *       Filename:  nta.c
 *
 *    Description:  zoj 1011
 *
 *        Version:  1.0
 *        Created:  2019-07-31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024

typedef struct _pair {
        int left;
        int right;
} pair;

typedef struct _transition {
        char elem;
        int sig;
        int size;
        pair ps[10];
} transition;

int n, m, k;
int level;
transition ts[150];
char tree[10][1024];

transition trans_filter(char s, int sig) {
        int i;
        for (i = 0; i < n * k; i++) {
                if (ts[i].elem == s && ts[i].sig == sig) {
                        break;
                }
        }
        return ts[i];
}

int main() {
        int i, j;
        int l, r;
        transition tmp;
        char s;
        while (1) {
                scanf("%d %d %d", &n, &m, &k);
                if (!n)
                        break;

                for (i = 0; i < n; i++) {
                        for (j = 0; j < k; j++) {
                                tmp.elem = 'a' + j;
                                tmp.sig = i;
                                tmp.size = 0;
                                s = '0';
                                while (s != '\n') {
                                        scanf("%d %d", &l, &r);
                                        s = getchar();
                                        tmp.ps[tmp.size].right = l;
                                        tmp.ps[tmp.size].left = r;
                                        tmp.size++;
                                }
                                ts[i * k + j] = tmp;
                        }
                }
                scanf("%d", &level);
                for (i = 0; i < level; i++) {
                        for (j = 0; j < i + 1; j++) {
                                scanf("%c", &tree[i][j]);
                        }
                }
        }

        return 0;
}
