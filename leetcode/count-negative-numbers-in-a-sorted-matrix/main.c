#include <stdio.h>
#include <stdlib.h>

/* 给你一个 m * n 的矩阵 grid，矩阵中的元素无论是按行还是按列，都以非递增顺序排列。  */

/* 请你统计并返回 grid 中 负数 的数目。 */

/* 示例 1： */

/* 输入：grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]] */
/* 输出：8 */
/* 解释：矩阵中共有 8 个负数。 */
/* 示例 2： */

/* 输入：grid = [[3,2],[1,0]] */
/* 输出：0 */
/* 示例 3： */

/* 输入：grid = [[1,-1],[-1,-1]] */
/* 输出：3 */
/* 示例 4： */

/* 输入：grid = [[-1]] */
/* 输出：1 */

/* 来源：力扣（LeetCode） */
/* 链接：https://leetcode-cn.com/problems/count-negative-numbers-in-a-sorted-matrix */
/* 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

int solve(int **grid, int gridSize, int *gridColSize, int l, int r, int L, int R) {
        if (l > r)
                return 0;

        int mid = l + ((r - l) >> 1);
        int pos = -1; // first negative position
        for (int i = L; i <= R; i++) {
                if (grid[mid][i] < 0) {
                        pos = i;
                        break;
                }
        }
        int ans = 0;
        if (pos >= 0) {
                ans += (gridColSize[0] - pos);
                ans += solve(grid, gridSize, gridColSize, l, mid - 1, pos, R);
                ans += solve(grid, gridSize, gridColSize, mid + 1, r, L, pos);
        } else {
                ans += solve(grid, gridSize, gridColSize, mid + 1, r, L, R);
        }
        return ans;
}
int countNegatives(int **grid, int gridSize, int *gridColSize) {
        return solve(grid, gridSize, gridColSize, 0, gridSize - 1, 0, gridColSize[0] - 1);
}
