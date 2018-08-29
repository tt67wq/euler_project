/*
 * =====================================================================================
 *
 *       Filename:  array.c
 *
 *    Description:  动态数组
 *
 *        Version:  1.0
 *        Created:  2018-08-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "array.h"
#include <stdio.h>
#include <stdlib.h>

void initArr(A *arr, int len) {
        arr->head = (ull *)malloc(sizeof(ull) * len);
        if (NULL == arr) {
                printf("Dynamic storage fail to distribute!");
                exit(-1);
        }
        arr->len = len;
        arr->num = 0;
        return;
}

bool isFull(A *arr) {
        if (arr->num >= arr->len) {
                return true;
        }
        return false;
}

bool isEmpty(A *arr) {
        if (arr->num == 0) {
                return true;
        }
        return false;
}

bool insert(A *arr, int index, ull val) {
        if (isFull(arr)) {
                return false;
        }
        if (index < 0 && index > arr->len - 1) {
                return false;
        }

        int temp = arr->len;
        while (temp > index) {
                arr->head[temp] = arr->head[temp - 1];
                --temp;
        }
        arr->head[index] = val;
        arr->num++;
        return true;
}

bool append(A *arr, ull val) {
        if (isFull(arr)) {
                return false;
        } else {
                arr->head[arr->num] = val;
                (arr->num)++;
        }
        return true;
}

bool remove_arr(A *arr, int index) {
        if (arr->num <= 0) {
                return false;
        }
        if (index < 0 && index > arr->num - 1) {
                return false;
        }
        int temp = index;
        while (temp < arr->num - 1) {
                arr->head[temp] = arr->head[temp + 1];
                temp++;
        }
        --arr->num;
        return true;
}

void show_arr(A *arr) {
        int i;
        for (i = 0; i < arr->num; i++)
                printf("%d -> %llu\n", i, arr->head[i]);

        printf("\n");
}

bool inverse(A *arr) {
        if (arr->num <= 0) {
                return false;
        }
        int temp = 0;
        int temp2 = arr->num;
        while (temp != temp2) {
                int x = arr->head[temp];
                arr->head[temp] = arr->head[temp2 - 1];
                arr->head[temp2 - 1] = x;
                temp++;
                temp2--;
        }
        return true;
}

bool replace(A *arr, int index, ull val) {
        if (arr->num <= 0 || index < 0 || index > arr->num - 1) {
                return false;
        }
        arr->head[index] = val;
        return true;
}
