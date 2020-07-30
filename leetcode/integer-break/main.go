package main

import "fmt"

const MaxUint = ^uint(0)
const MinUint = 0
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

func max(nums ...int) int {
	var m int = MinInt
	for _, num := range nums {
		if m < num {
			m = num
		}
	}
	return m
}

func integerBreak(n int) int {

	var dp []int = make([]int, n+1)
	dp[0] = 1
	dp[1] = 1

	for i := 2; i < n+1; i++ {
		dp[i] = MinInt
		for j := 1; j < i; j++ {
			tmp := max(j*(i-j), j*dp[i-j])
			dp[i] = max(tmp, dp[i])
		}
	}

	return dp[n]
}

func main() {
	fmt.Println(integerBreak(10))
	return
}
