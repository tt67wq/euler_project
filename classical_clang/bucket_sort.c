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

/*
 * 桶排序
 *
 * 参数说明：
 *     a -- 待排序数组
 *     n -- 数组a的长度
 *     max -- 数组a中最大值的范围
 */
void bucketSort(int a[], int n, int max) {
        int i, j;
        int buckets[max];

        // 将buckets中的所有数据都初始化为0。
        memset(buckets, 0, max * sizeof(int));

        // 1. 计数
        for (i = 0; i < n; i++)
                buckets[a[i]]++;

        // 2. 排序
        for (i = 0, j = 0; i < max; i++) {
                while ((buckets[i]--) > 0)
                        a[j++] = i;
        }
}
