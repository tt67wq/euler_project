package main

import (
	"fmt"
)

func max(nums ...int) int {
	var m, n int
	m = -1000000

	for _, n = range nums {
		if n > m {
			m = n
		}
	}
	return m
}

func maxProfit(prices []int) int {

	var m, ans, i int
	m = 0
	ans = 0

	for i = len(prices) - 1; i >= 0; i-- {
		ans = max(ans, m-prices[i])
		if prices[i] > m {
			m = prices[i]
		}
	}
	return ans
}

func main() {}
