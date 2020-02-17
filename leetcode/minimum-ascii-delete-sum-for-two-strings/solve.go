package main

import (
	"fmt"
)

const MaxUint = ^uint(0)
const MinUint = 0
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

func minimumDeleteSum(s1 string, s2 string) int {
	var i, j, l1, l2 int
	var dp [][]int // dp[i][j] 表示 minimumdeletesum(s[i:], s[j:]), ans = dp[0][0]

	l1 = len(s1)
	l2 = len(s2)

	dp = make([][]int, l1+1)
	for i = 0; i < l1+1; i++ {
		dp[i] = make([]int, l2+1)
	}

	dp[l1][l2] = 0
	// 当 s1[i:] 和 s2[j:] 中的某一个字符串为空时，dp[i][j] 的值即为另一个非空字符串的所有字符的 ASCII 值之和
	for i = l1 - 1; i >= 0; i-- {
		dp[i][l2] = dp[i+1][l2] + int(s1[i])
	}

	for j = l2 - 1; j >= 0; j-- {
		dp[l1][j] = dp[l1][j+1] + int(s2[j])
	}

	for i = l1 - 1; i >= 0; i-- {
		for j = l2 - 1; j >= 0; j-- {
			// 相同字母，不用修改
			// 不同字母，选较小代价的修改
			if s1[i] == s2[j] {
				dp[i][j] = dp[i+1][j+1]
			} else {
				dp[i][j] = min(dp[i][j+1]+int(s2[j]), dp[i+1][j]+int(s1[i]))
			}

		}
	}
	// for i = 0; i < l1+1; i++ {
	// 	for j = 0; j < l2+1; j++ {
	// 		fmt.Print(dp[i][j], "\t")
	// 	}
	// 	fmt.Print("\n")
	// }

	return dp[0][0]
}

func min(nums ...int) int {
	var m int

	m = MaxInt

	for _, num := range nums {
		if num < m {
			m = num
		}
	}
	return m
}

func main() {

	fmt.Println(minimumDeleteSum("delete", "leet"))
	fmt.Println(minimumDeleteSum("sea", "eat"))
}
