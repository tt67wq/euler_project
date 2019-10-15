/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* https://leetcode-cn.com/problems/maximum-number-of-balloons/ */

#include <stdio.h>
#include <stdlib.h>

#define B 0
#define A 1
#define L 2
#define O 3
#define N 4
#define MAX 1e5

int maxNumberOfBalloons(char *text) {
        int i;
        int s = MAX;
        int cs[5] = {0};
        for (i = 0;; i++) {
                if (text[i] == '\0')
                        break;
                if (text[i] == 'b')
                        cs[B] += 1;
                if (text[i] == 'a')
                        cs[A] += 1;
                if (text[i] == 'l')
                        cs[L] += 1;
                if (text[i] == 'o')
                        cs[O] += 1;
                if (text[i] == 'n')
                        cs[N] += 1;
        }
        cs[L] /= 2;
        cs[O] /= 2;
        for (i = 0; i < 5; i++) {
                if (cs[i] < s)
                        s = cs[i];
        }
        return s;
}

int main() {
        char *text;
        text = (char *)calloc(1000, sizeof(char));
        while (1) {
                scanf("%s", text);
                printf("%d\n", maxNumberOfBalloons(text));
        }
        return 0;
}
