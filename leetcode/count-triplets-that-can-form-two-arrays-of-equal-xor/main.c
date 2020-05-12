/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-12
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

int countTriplets(int *arr, int arrSize) {
        int cnt = 0;
        for (int i = 0; i < arrSize; i++) {
                int a = arr[i];
                for (int j = i + 1; j < arrSize; j++) {
                        a ^= arr[j]; // a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]^ arr[j]
                        int b = arr[j];
                        for (int k = j; k < arrSize; k++) {
                                b ^= arr[k]; // b = arr[j] ^ arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
                                if (a == b) {
                                        cnt++;
                                }
                        }
                }
        }
        return cnt;
}

int main() { return 0; }
