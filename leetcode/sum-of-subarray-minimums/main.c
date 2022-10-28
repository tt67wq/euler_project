/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-28
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。

// 由于答案可能很大，因此 返回答案模 10^9 + 7 。

//  

// 示例 1：

// 输入：arr = [3,1,2,4]
// 输出：17
// 解释：
// 子数组为 [3]，[1]，[2]，[4]，[3,1]，[1,2]，[2,4]，[3,1,2]，[1,2,4]，[3,1,2,4]。
// 最小值为 3，1，2，4，1，1，2，1，1，1，和为 17。
// 示例 2：

// 输入：arr = [11,81,94,43,3]
// 输出：444
//  

// 提示：

// 1 <= arr.length <= 3 * 104
// 1 <= arr[i] <= 3 * 104

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/sum-of-subarray-minimums
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

typedef struct _stack {
        int *data;
        int size;
        int top;
} stack;

#define MINSIZE 64
#define MAXSIZE 30000

#define STACK_TOP(st) ((st)->data[(st)->top])
#define IS_EMPTY(st) ((st)->top == -1)
#define POP(st) (pop((st)))
#define PUSH(st, item) (push((st), (item)))
#define CLEAN(st) (cleanStack((st)))

stack *newStack() {
        stack *st;
        st = (stack *)calloc(1, sizeof(stack));
        st->top = -1;
        st->size = MINSIZE;
        st->data = (int *)calloc(st->size, sizeof(int));
        return st;
}

void cleanStack(stack *st) {
        if (st != NULL) {
                free(st->data);
                st->top = -1;
                st->size = MINSIZE;
                st->data = (int *)calloc(st->size, sizeof(int));
        }
}
void releaseStack(stack *st) {
        if (st != NULL) {
                free(st->data);
                free(st);
        }
}

void push(stack *st, int item) {
        st->data[++st->top] = item;
        if ((float)st->top / st->size > 0.8 && st->size < MAXSIZE) {
                st->size <<= 1;
                st->data = (int *)realloc(st->data, sizeof(int) * st->size);
        }
}

int pop(stack *st) {
        int r;
        r = st->data[st->top--];
        if ((float)st->top / st->size < 0.3 && st->size > MINSIZE) {
                st->size >>= 1;
                st->data = (int *)realloc(st->data, sizeof(int) * st->size);
        }
        return r;
}

int sumSubarrayMins(int *arr, int arrSize) {
        int *left = (int *)calloc(arrSize, sizeof(int));
        int *right = (int *)calloc(arrSize, sizeof(int));
        stack *st = newStack();
        for (int i = 0; i < arrSize; i++) {
                while (!IS_EMPTY(st) && arr[i] <= arr[STACK_TOP(st)]) {
                        POP(st);
                }
                left[i] = i - (IS_EMPTY(st) ? -1 : STACK_TOP(st));
                PUSH(st, i);
        }
        CLEAN(st);
        for (int i = arrSize - 1; i >= 0; i--) {
                while (!IS_EMPTY(st) && arr[i] < arr[STACK_TOP(st)]) {
                        POP(st);
                }
                right[i] = (IS_EMPTY(st) ? arrSize : STACK_TOP(st)) - i;
                PUSH(st, i);
        }

        int ans = 0;
        uint64_t mod = 1e9 + 7;
        for (int i = 0; i < arrSize; i++) {
                ans = (ans + (uint64_t)left[i] * right[i] * arr[i]) % mod;
        }
        return ans;
}

int main() {
        int arr[] = {11, 81, 94, 43, 3};
        printf("%d\n", sumSubarrayMins(arr, 5));
        return 0;
}