/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-12
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int canCompleteCircuit(int *gas, int gasSize, int *cost, int costSize) {
        int i, j, s;

        for (i = 0; i < gasSize; i++) {
                j = i;
                s = 0;
                do {
                        s += (gas[j] - cost[j]);
                        if (s < 0)
                                break;
                        j++;
                        if (j == gasSize)
                                j = 0;

                } while (j != i);
                if (j == i && s >= 0)
                        return i;
        }
        return -1;
}

int main() {
        int gas[] = {1, 2, 3, 4, 5};
        int cos[] = {3, 4, 5, 1, 2};

        printf("%d\n", canCompleteCircuit(gas, 5, cos, 5));

        return 0;
}
