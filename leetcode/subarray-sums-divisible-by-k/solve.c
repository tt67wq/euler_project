/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-07
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int subarraysDivByK(int *A, int ASize, int K) {
        if (ASize == 0)
                return 0;

        int i, t, ans, *prefix, *cnt;

        prefix = (int *)calloc(ASize, sizeof(int));
        cnt = (int *)calloc(K, sizeof(int));
        ans = 0;

        // 前缀和
        prefix[0] = A[0];
        for (i = 1; i < ASize; i++)
                prefix[i] = prefix[i - 1] + A[i];

        // mod 计数
        for (i = 0; i < ASize; i++) {
                t = prefix[i] % K;
                if (t < 0)
                        t += K;
                cnt[t] += 1;
        }

        // 一个元素都不选也是一种情况
        cnt[0] += 1;

        // 同一mod做差
        for (i = 0; i < K; i++)
                ans += cnt[i] * (cnt[i] - 1) / 2;

        free(prefix);
        free(cnt);
        return ans;
}

int main() {
        int A[] = {-2};
        printf("%d\n", subarraysDivByK(A, 1, 6));
        return 0;
}
