// https://leetcode.cn/problems/make-two-arrays-equal-by-reversing-subarrays/

// 给你两个长度相同的整数数组 target 和 arr 。每一步中，你可以选择 arr 的任意 非空子数组 并将它翻转。你可以执行此过程任意次。

// 如果你能让 arr 变得与 target 相同，返回 True；否则，返回 False 。

// 示例 1：

// 输入：target = [1,2,3,4], arr = [2,4,1,3]
// 输出：true
// 解释：你可以按照如下步骤使 arr 变成 target：
// 1- 翻转子数组 [2,4,1] ，arr 变成 [1,4,2,3]
// 2- 翻转子数组 [4,2] ，arr 变成 [1,2,4,3]
// 3- 翻转子数组 [4,3] ，arr 变成 [1,2,3,4]
// 上述方法并不是唯一的，还存在多种将 arr 变成 target 的方法。
// 示例 2：

// 输入：target = [7], arr = [7]
// 输出：true
// 解释：arr 不需要做任何翻转已经与 target 相等。
// 示例 3：

// 输入：target = [3,7,9], arr = [3,7,11]
// 输出：false
// 解释：arr 没有数字 9 ，所以无论如何也无法变成 target 。

pub struct Solution {}
impl Solution {
    pub fn can_be_equal(mut target: Vec<i32>, mut arr: Vec<i32>) -> bool {
        target.sort();
        arr.sort();
        target == arr
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_can_be_equal_true() {
        let target = vec![1, 2, 3, 4];
        let arr = vec![2, 4, 1, 3];
        assert_eq!(Solution::can_be_equal(target, arr), true);
    }

    #[test]
    fn test_can_be_equal_true_single_element() {
        let target = vec![7];
        let arr = vec![7];
        assert_eq!(Solution::can_be_equal(target, arr), true);
    }

    #[test]
    fn test_can_be_equal_false() {
        let target = vec![3, 7, 9];
        let arr = vec![3, 7, 11];
        assert_eq!(Solution::can_be_equal(target, arr), false);
    }
}
