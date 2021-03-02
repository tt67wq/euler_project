#include <stdio.h>
#include <stdlib.h>

/* 给定一个整数数组  nums，求出数组从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点。 */

/* 实现 NumArray 类： */

/* NumArray(int[] nums) 使用数组 nums 初始化对象 */
/* int sumRange(int i, int j) 返回数组 nums 从索引 i 到 j（i ≤ j）范围内元素的总
和，包含 i、j 两点（也就是 sum(nums[i], nums[i + 1], ... , nums[j])） */

/* 示例： */

/* 输入： */
/* ["NumArray", "sumRange", "sumRange", "sumRange"] */
/* [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]] */
/* 输出： */
/* [null, 1, -1, -3] */

/* 解释： */
/* NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]); */
/* numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3) */
/* numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1))  */
/* numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1)) */

/* 提示： */

/* 0 <= nums.length <= 104 */
/* -105 <= nums[i] <= 105 */
/* 0 <= i <= j < nums.length */
/* 最多调用 104 次 sumRange 方法 */

typedef struct {
        int *prefixSum; // prefixSum[i] = sum of nums[0: i)
} NumArray;

NumArray *numArrayCreate(int *nums, int numsSize) {
        NumArray *obj;
        obj = (NumArray *)malloc(sizeof(NumArray));
        obj->prefixSum = (int *)malloc(sizeof(int) * (1 + numsSize));
        int prefixSum = 0;
        obj->prefixSum[0] = 0;
        for (int i = 0; i < numsSize; i++) {
                prefixSum += nums[i];
                obj->prefixSum[i + 1] = prefixSum;
        }
        return obj;
}

int numArraySumRange(NumArray *obj, int i, int j) {
        return obj->prefixSum[j + 1] - obj->prefixSum[i];
}

void numArrayFree(NumArray *obj) {
        free(obj->prefixSum);
        free(obj);
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, i, j);

 * numArrayFree(obj);
*/

int main() { return 0; }
