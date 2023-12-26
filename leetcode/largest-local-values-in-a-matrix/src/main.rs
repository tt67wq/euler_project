// https://leetcode.cn/problems/largest-local-values-in-a-matrix/

// You are given an n x n integer matrix grid.

// Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:

// maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.
// In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.

// Return the generated matrix.

pub struct Solution {}

impl Solution {
    fn get_max(grid: &Vec<Vec<i32>>, i: usize, j: usize) -> i32 {
        let mut max = grid[i][j];
        for x in i - 1..=i + 1 {
            for y in j - 1..=j + 1 {
                if grid[x][y] > max {
                    max = grid[x][y];
                }
            }
        }
        max
    }
    pub fn largest_local(grid: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let n = grid.len();
        let mut ret = vec![vec![0; n - 2]; n - 2];
        for i in 0..n - 2 {
            for j in 0..n - 2 {
                ret[i][j] = Solution::get_max(&grid, i + 1, j + 1);
            }
        }
        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_largest_local() {
        let grid = vec![
            vec![1, 2, 3, 4],
            vec![5, 6, 7, 8],
            vec![9, 10, 11, 12],
            vec![13, 14, 15, 16],
        ];
        let expected = vec![vec![11, 12], vec![15, 16]];
        assert_eq!(Solution::largest_local(grid), expected);
    }

    #[test]
    fn test_largest_local_negative_numbers() {
        let grid = vec![vec![-1, -2, -3], vec![-4, -5, -6], vec![-7, -8, -9]];
        let expected = vec![vec![-1]];
        assert_eq!(Solution::largest_local(grid), expected);
    }
}
