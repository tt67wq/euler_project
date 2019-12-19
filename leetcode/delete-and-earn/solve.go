package main

import "fmt"

func max(ns ...int) int {
	if len(ns) == 1 {
		return ns[0]
	}
	var m, i int

	m = ns[0]

	for i = 1; i < len(ns); i++ {
		if ns[i] > m {
			m = ns[i]
		}
	}
	return m
}

func deleteAndEarn(nums []int) int {
	var trans []int = make([]int, 10001)
	var i, l int
	var dp []int = make([]int, 10001)

	l = len(nums)

	for i = 0; i < l; i++ {
		trans[nums[i]] += nums[i]
	}

	dp[0] = 0
	dp[1] = trans[1]

	for i = 2; i < len(trans); i++ {
		dp[i] = max(dp[i-1], dp[i-2]+trans[i])
	}
	return dp[len(dp)-1]
}

func main() {
	fmt.Println(deleteAndEarn([]int{3, 4, 2}))
}
