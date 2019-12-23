package main

import (
	"fmt"
)

func maxProfit(prices []int) int {
	var i, l int
	var dp []int

	l = len(prices)
	if l <= 1 {
		return 0
	}
	dp = make([]int, l)
	dp[0] = 0

	for i = 1; i < l; i++ {
		if prices[i] > prices[i-1] {
			dp[i] = dp[i-1] + prices[i] - prices[i-1]
		} else {
			dp[i] = dp[i-1]
		}
	}

	return dp[l-1]
}

func main() {
	fmt.Println(maxProfit([]int{7, 1, 5, 3, 6, 4}))
	fmt.Println(maxProfit([]int{1, 2, 3, 4, 5}))
	fmt.Println(maxProfit([]int{7, 6, 4, 3, 2, 1}))
}
