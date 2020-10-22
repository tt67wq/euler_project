/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-10-22
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int minCost(char *s, int *cost, int costSize) {
        int i = 0, res = 0;
        while (i < costSize) {
                char ch = s[i];
                int maxValue = 0;
                int sum = 0;

                while (i < costSize && s[i] == ch) {
                        maxValue = maxValue > cost[i] ? maxValue : cost[i];
                        sum += cost[i];
                        i++;
                }
                res += (sum - maxValue);
        }
        return res;
}

int main() {
        char s[] = "aabaa";
        int cost[] = {1, 2, 3, 4, 1};
        int res = minCost(s, cost, 5);
        printf("%d\n", res);
        return 0;
}