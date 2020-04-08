/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-08
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int numTimesAllBlue(int *light, int lightSize) {
        int m = 0, ans = 0;
        for (int i = 0; i < lightSize; i++) {
                m = m > light[i] ? m : light[i];
                if (i + 1 == m) {
                        ans++;
                }
        }
        return ans;
}

int main() {
        int light[] = {2, 1, 3, 5, 4};
        printf("%d\n", numTimesAllBlue(light, 5));
        return 0;
}
