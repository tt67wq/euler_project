// https://leetcode.cn/problems/number-of-boomerangs/

pub struct Solution {}

use std::collections::HashMap;

impl Solution {
    pub fn calaDist(x: &Vec<i32>, y: &Vec<i32>) -> i32 {
        let distx = x[0] - y[0];
        let disty = x[1] - y[1];
        distx * distx + disty * disty
    }

    pub fn number_of_boomerangs(points: Vec<Vec<i32>>) -> i32 {
        let mut count: i32 = 0;
        for (i, ival) in points.iter().enumerate() {
            let mut map: HashMap<i32, i32> = HashMap::new();
            for (j, jval) in points.iter().enumerate() {
                if i == j {
                    continue;
                }
                let dist = Self::calaDist(ival, jval);
                *map.entry(dist).or_insert(0) += 1;
            }
            for (_, val) in map.iter() {
                if *val >= 2 {
                    count += val * (val - 1);
                }
            }
        }
        count
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_calaDist() {
        let x = vec![0, 0];
        let y = vec![3, 4];
        assert_eq!(Solution::calaDist(&x, &y), 25);
    }

    #[test]
    fn test_number_of_boomerangs() {
        let points = vec![vec![0, 0], vec![1, 0], vec![2, 0]];
        assert_eq!(Solution::number_of_boomerangs(points), 2);

        let points = vec![vec![0, 0], vec![1, 0], vec![2, 0], vec![3, 0]];
        assert_eq!(Solution::number_of_boomerangs(points), 4);

        let points = vec![vec![0, 0], vec![1, 1], vec![2, 2]];
        assert_eq!(Solution::number_of_boomerangs(points), 2);

        let points = vec![vec![0, 0], vec![1, 1], vec![2, 2], vec![3, 3]];
        assert_eq!(Solution::number_of_boomerangs(points), 4);
    }
}
