package main

import (
	"fmt"
)

// 给你一个整数数组 nums ，返回数组中最大数和最小数的 最大公约数 。

// 两个数的 最大公约数 是能够被两个数整除的最大正整数。

//

// 示例 1：

// 输入：nums = [2,5,6,9,10]
// 输出：2
// 解释：
// nums 中最小的数是 2
// nums 中最大的数是 10
// 2 和 10 的最大公约数是 2
// 示例 2：

// 输入：nums = [7,5,6,8,3]
// 输出：1
// 解释：
// nums 中最小的数是 3
// nums 中最大的数是 8
// 3 和 8 的最大公约数是 1
// 示例 3：

// 输入：nums = [3,3]
// 输出：3
// 解释：
// nums 中最小的数是 3
// nums 中最大的数是 3
// 3 和 3 的最大公约数是 3
//

// 提示：

// 2 <= nums.length <= 1000
// 1 <= nums[i] <= 1000

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/find-greatest-common-divisor-of-array
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// Constant definitions
const MaxUint = ^uint(0)
const MinUint = 0

const MaxInt = int(^uint(0) >> 1)
const MinInt = -MaxInt - 1

func findGCD(nums []int) int {
	var max, min int
	max = MinInt
	min = MaxInt

	for _, i := range nums {
		if i > max {
			max = i
		}
		if i < min {
			min = i
		}
	}
	return gcd(max, min)
}

func gcd(m, n int) int {
	if m < n {
		t := m
		m = n
		n = t
	}
	i := m % n
	for i > 0 {
		m = n
		n = i
		i = m % n
	}
	return n
}

func main() {
	fmt.Println(findGCD([]int{2, 5, 6, 9, 10}))
	fmt.Println(findGCD([]int{7, 5, 6, 8, 3}))
	fmt.Println(findGCD([]int{3, 3}))
}
