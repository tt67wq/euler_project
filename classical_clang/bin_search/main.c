/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-21
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

int binarySearch(int a[], int n, int key) {
        int low = 0;
        int high = n - 1;
        while (low <= high) {
                int mid = low + (high - low) / 2;
                int midVal = a[mid];
                if (midVal < key)
                        low = mid + 1;
                else if (midVal > key)
                        high = mid - 1;
                else
                        return mid;
        }
        return -1;
}
int main() {
        int i, val, ret;
        int a[8] = {-32, 12, 16, 24, 36, 45, 59, 98};
        for (i = 0; i < 8; i++)
                printf("%d\t", a[i]);
        printf("\n请输人所要查找的元素：");
        scanf("%d", &val);
        ret = binarySearch(a, 8, val);
        if (-1 == ret)
                printf("查找失败 \n");
        else
                printf("查找成功 \n");
        return 0;
}
