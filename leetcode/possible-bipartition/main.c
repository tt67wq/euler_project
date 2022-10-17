/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-17
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 给定一组 n 人（编号为 1, 2, ...,
// n）， 我们想把每个人分进任意大小的两组。每个人都可能不喜欢其他人，那么他们不应该属于同一组。

// 给定整数 n 和数组 dislikes ，其中 dislikes[i] = [ai, bi] ，表示不允许将编号为
// ai 和  bi的人归入同一组。当可以用这种方法将所有人分进两组时，返回 true；否则返回 false。

//  

// 示例 1：

// 输入：n = 4, dislikes = [[1,2],[1,3],[2,4]]
// 输出：true
// 解释：group1 [1,4], group2 [2,3]
// 示例 2：

// 输入：n = 3, dislikes = [[1,2],[1,3],[2,3]]
// 输出：false
// 示例 3：

// 输入：n = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
// 输出：false
//  

// 提示：

// 1 <= n <= 2000
// 0 <= dislikes.length <= 104
// dislikes[i].length == 2
// 1 <= dislikes[i][j] <= n
// ai < bi
// dislikes 中每一组都 不同

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/possible-bipartition
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define N 4005
#define SET(m, a, b) (m[0] = a, m[1] = b)

typedef struct {
        int root;
        int rank;
} dset;

dset s[N] = {{0, 0}};

void init() {
        for (int i = 0; i < N; i++) {
                s[i].root = 0;
                s[i].rank = 0;
        }
}

dset find(dset *s, int k) {
        if (s[k].root == 0) {
                // new member
                s[k].root = k;
                s[k].rank = 1;
                return s[k];
        }

        if (s[k].root == k) {
                return s[k];
        }
        s[k] = find(s, s[k].root);

        return s[k];
}

void merge(dset *s, int m, int n) {
        dset ms = find(s, m);
        dset ns = find(s, n);

        // merge small one into big one
        if (ms.rank <= ns.rank) {
                s[ms.root].root = ns.root;
        } else {
                s[ns.root].root = ms.root;
        }
        if (s[ms.root].rank != s[ns.root].rank && s[ms.root].root != s[ns.root].root) {
                s[ns.root].rank++;
        }
}

bool possibleBipartition(int n, int **dislikes, int dislikesSize, int *dislikesColSize) {
        init();
        for (int i = 0; i < dislikesSize; i++) {
                int *dislike = dislikes[i];
                dset a = find(s, dislike[0]), b = find(s, dislike[1]);
                if (a.root == b.root)
                        return false;

                merge(s, a.root + n, b.root);
                merge(s, b.root + n, a.root);
        }
        return true;
}
int main() {
        int sz = 4, n = 5;
        int **dislikes = (int **)malloc(sizeof(int *) * sz);
        for (int i = 0; i < sz; i++) {
                dislikes[i] = (int *)malloc(sizeof(int) * 2);
        }
        SET(dislikes[0], 1, 2);
        SET(dislikes[1], 1, 3);
        SET(dislikes[2], 1, 4);
        SET(dislikes[3], 1, 5);

        printf("%d\n", possibleBipartition(n, dislikes, sz, NULL));
        return 0;
}