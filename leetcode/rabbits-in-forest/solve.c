/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-26
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int numRabbits(int *answers, int answersSize) {
        if (answersSize == 0)
                return 0;

        int i, s = 0, mx = 0;
        int cs[1000] = {0};

        for (i = 0; i < answersSize; i++) {
                cs[answers[i]]++;
                mx = answers[i] > mx ? answers[i] : mx;
        }

        s += cs[0];
        for (i = 1; i < mx + 1; i++)
                s += (int)ceil((double)cs[i] / (i + 1)) * (i + 1);

        return s;
}

int main() {
        printf("%d\n", (int)ceil((double)3 / 2));
        printf("%d\n", (int)ceil(3 / 2) * 2);
        return 0;
}
