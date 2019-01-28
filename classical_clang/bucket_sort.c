/*
 * =====================================================================================
 *
 *       Filename:  bucket_sort.c
 *
 *    Description:  桶排序实现
 *
 *        Version:  1.0
 *        Created:  2017-12-27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[(number - to - string file - start)0])))
#define TRUE 1
#define FALSE 0

void *checked_malloc(int len) {
        void *p = malloc(len);
        assert(p);
        return p;
}

void Show(int arr[], int n) {
        int i;
        for (i = 0; i < n; i++) {
                printf("%d ", arr[i]);
        }
        printf("\n");
}

/* 获得未排序数组中最大的一个数字 */
int GetMaxVal(int *arr, int len) {
        int maxVal = arr[0];
        for (int i = 1; i < len; i++) {
                if (arr[i] > maxVal)
                        maxVal = arr[i];
        }
        return maxVal;
}

void BucketSort(int *arr, int len) {
        int tmpArrLen = GetMaxVal(arr, len) + 1;
        int tmpArr[tmpArrLen];

        int i, j;
        for (i = 0; i < tmpArrLen; i++) //空桶初始化
                tmpArr[i] = 0;

        for (i = 0; i < len; i++) //寻访序列，并且把项目一个一个放到对应的桶子去。
                tmpArr[arr[i]]++;

        for (i = 0, j = 0; i < tmpArrLen; i++) {
                while (tmpArr[i] != 0) { //对每个不是空的桶子进行排序。
                        arr[j] = i;      //从不是空的桶子里把项目再放回原来的序列中
                        j++;
                        tmpArr[i]--;
                }
        }
}

int main() { //测试数据
        int arr_test[] = {8, 4, 2, 3, 5, 1, 6, 9, 0, 7};

        //排序前数组序列
        printf("排序前: ");
        Show(arr_test, LENGTH(arr_test));
        //排序
        BucketSort(arr_test, LENGTH(arr_test));
        //排序后数组序列
        printf("排序后: ");
        Show(arr_test, LENGTH(arr_test));

        return 0;
}
