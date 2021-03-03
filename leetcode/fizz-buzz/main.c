/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  main.c
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* 写一个程序，输出从 1 到 n 数字的字符串表示。 */

/* 1. 如果 n 是3的倍数，输出“Fizz”； */

/* 2. 如果 n 是5的倍数，输出“Buzz”； */

/* 3.如果 n 同时是3和5的倍数，输出 “FizzBuzz”。 */

/* 示例： */
/* n = 15, */

/* 返回: */
/* [ */
/*     "1", */
/*     "2", */
/*     "Fizz", */
/*     "4", */
/*     "Buzz", */
/*     "Fizz", */
/*     "7", */
/*     "8", */
/*     "Fizz", */
/*     "Buzz", */
/*     "11", */
/*     "Fizz", */
/*     "13", */
/*     "14", */
/*     "FizzBuzz" */
/* ] */

/* 来源：力扣（LeetCode） */
/* 链接：https://leetcode-cn.com/problems/fizz-buzz */
/* 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **fizzBuzz(int n, int *returnSize) {
        char **ans = (char **)malloc(sizeof(char *) * n);
        for (int i = 1; i <= n; i++) {
                int a = i % 3, b = i % 5;
                if (a == 0 && b == 0) {
                        ans[i - 1] = "FizzBuzz";
                } else if (a == 0) {
                        ans[i - 1] = "Fizz";
                } else if (b == 0) {
                        ans[i - 1] = "Buzz";
                } else {
                        ans[i - 1] = (char *)malloc(sizeof(char) * 10);
                        sprintf(ans[i - 1], "%d", i);
                }
        }
        *returnSize = n;
        return ans;
}

int main() {
        int returnSize;
        char **ans = fizzBuzz(15, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                puts(ans[i]);
        }
        return 0;
}
