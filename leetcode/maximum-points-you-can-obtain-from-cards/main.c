/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-07
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

int maxScore(int *cardPoints, int cardPointsSize, int k) {
        int res, *prefixSum, i, l, r;
        size_t _size;

        _size = sizeof(int) * (cardPointsSize * 2 + 1);
        prefixSum = malloc(_size);
        prefixSum[0] = 0;
        for (i = 1; i < cardPointsSize + 1; i++) {
                prefixSum[i] = cardPoints[i - 1];
                prefixSum[i + cardPointsSize] = cardPoints[i - 1];
        }
        for (i = 1; i < cardPointsSize << 1; i++) {
                prefixSum[i] += prefixSum[i - 1];
        }
        l = cardPointsSize - k, r = cardPointsSize;
        res = 0;
        while (l <= cardPointsSize) {
                res = MAX(prefixSum[r] - prefixSum[l], res);
                l++;
                r++;
        }

        free(prefixSum);
        return res;
}

int main() {
        int cardPoints[] = {11, 49, 100, 20, 86, 29, 72};
        printf("%d\n", maxScore(cardPoints, ARRAY_SIZE(cardPoints), 4));
        return 0;
}