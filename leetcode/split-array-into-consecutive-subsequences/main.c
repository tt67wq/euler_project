/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-25
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

bool isPossible(int *nums, int numsSize) {
        int max = INT32_MIN;
        int min = INT32_MAX;
        for (int i = 0; i < numsSize; i++) {
                max = MAX(max, nums[i]);
                min = MIN(min, nums[i]);
        }
        max++, min--; //确保放得下
        int len = max - min;
        int *table = (int *)calloc(len, sizeof(int));

        for (int i = 0; i < numsSize; i++) {
                table[nums[i] - min]++;
        }

        for (int i = 0; i < len; i++) {
                while (table[i] > 0) {
                        int j = 0;
                        while (j < 3 && i + j < len) { //至少减掉三个
                                table[i + j]--;
                                j++;
                        }
                        if (j != 3)
                                return 0; //中途break就说明不符合

                        while ((i + j < len) &&
                               (table[i + j - 1] < table[i + j])) { //如果前数小于后数仍然继续减
                                table[i + j]--;
                                j++;
                        }
                }
        }

        bool ans = true;
        for (int i = 0; i < len; i++) {
                if (table[i] != 0) {
                        ans = false;
                        break;
                }
        }
        free(table);
        return ans;
}

int main() {
        int nums[] = {1, 2, 3, 3, 4, 5};
        int ans = isPossible(nums, 6);
        printf("%d\n", ans);
        return 0;
}