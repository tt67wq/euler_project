pub struct Solution {}

impl Solution {
    pub fn min_operations(grid: Vec<Vec<i32>>, x: i32) -> i32 {
        let a = grid[0][0] % x;
        let mut cnt = vec![];
        for v in grid {
            for n in v {
                if n % x != a {
                    return -1;
                }
                cnt.push(n / x);
            }
        }

        cnt.sort_unstable();
        let mid = cnt[cnt.len() / 2];
        let mut ans = 0;
        for n in cnt {
            ans += (n - mid).abs();
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_min_operations_all_elements_equal() {
        let grid = vec![vec![2, 4, 6], vec![8, 10, 12]];
        let x = 2;
        assert_eq!(Solution::min_operations(grid, x), 9);
    }

    #[test]
    fn test_min_operations_impossible() {
        let grid = vec![vec![1, 3, 5], vec![7, 9, 11]];
        let x = 2;
        assert_eq!(Solution::min_operations(grid, x), 9);
    }

    #[test]
    fn test_min_operations_odd_number_of_elements() {
        let grid = vec![vec![1, 3, 5], vec![7, 9, 11], vec![13, 15, 17]];
        let x = 2;
        assert_eq!(Solution::min_operations(grid, x), 20);
    }

    #[test]
    fn test_min_operations_even_number_of_elements() {
        let grid = vec![vec![1, 3, 5, 7], vec![9, 11, 13, 15]];
        let x = 2;
        assert_eq!(Solution::min_operations(grid, x), 16);
    }
}
