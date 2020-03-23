/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-23
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* [idi, ratingi, veganFriendlyi, pricei, distancei] */
int *filterRestaurants(int **restaurants, int restaurantsSize, int *restaurantsColSize,
                       int veganFriendly, int maxPrice, int maxDistance, int *returnSize) {

        int *vis = (int *)calloc(restaurantsSize,
                                 sizeof(int)); // vis[i] == 1 -> restaurants[i] is cancelled

        *returnSize = restaurantsSize;
        // filter
        for (int i = 0; i < restaurantsSize; i++) {
                if (veganFriendly == 1 && restaurants[i][2] == 0) {
                        vis[i] = 1;
                        (*returnSize)--;
                        continue;
                }
                if (restaurants[i][3] > maxPrice) {
                        vis[i] = 1;
                        (*returnSize)--;
                        continue;
                }
                if (restaurants[i][4] > maxDistance) {
                        vis[i] = 1;
                        (*returnSize)--;
                        continue;
                }
        }

        int *ans = (int *)calloc(*returnSize, sizeof(int));
        {
                int j = 0;
                for (int i = 0; i < restaurantsSize; i++) {
                        if (vis[i] == 0) {
                                ans[j++] = i;
                        }
                }
        }

        // rank
        // 过滤后返回餐馆的 id，按照 rating 从高到低排序。如果 rating 相同，那么按 id 从高到低排序
        for (int i = 0; i + 1 < *returnSize; i++) {
                for (int j = i + 1; j < *returnSize; j++) {
                        if (restaurants[ans[i]][1] < restaurants[ans[j]][1]) {
                                int k = ans[i];
                                ans[i] = ans[j];
                                ans[j] = k;
                        } else if (restaurants[ans[i]][1] > restaurants[ans[j]][1]) {
                                // pass
                        } else {
                                if (restaurants[ans[i]][0] < restaurants[ans[j]][0]) {
                                        int k = ans[i];
                                        ans[i] = ans[j];
                                        ans[j] = k;
                                }
                        }
                }
        }

        for (int i = 0; i < *returnSize; i++) {
                ans[i] = restaurants[ans[i]][0];
        }
        free(vis);
        return ans;
}

int main() {
        int restaurant0[] = {1, 4, 1, 40, 10};
        int restaurant1[] = {2, 8, 0, 50, 5};
        int restaurant2[] = {3, 8, 1, 30, 4};
        int restaurant3[] = {4, 10, 0, 10, 3};
        int restaurant4[] = {5, 1, 1, 15, 1};

        int **rs = (int **)calloc(5, sizeof(int *));
        rs[0] = restaurant0;
        rs[1] = restaurant1;
        rs[2] = restaurant2;
        rs[3] = restaurant3;
        rs[4] = restaurant4;

        int returnSize = 0;
        int *ans = filterRestaurants(rs, 5, NULL, 1, 50, 10, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", ans[i]);
        }
        printf("\n");
        free(rs);
        free(ans);
        return 0;
}
