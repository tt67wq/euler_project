package main

import (
	"fmt"
)

const MaxUint = ^uint(0)
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

func maxProfit(prices []int) int {

	var l int = len(prices)
	var b1, s1, b2, s2, p, i int

	b1 = MinInt
	s1 = 0
	b2 = MinInt
	s2 = 0

	for i = 0; i < l; i++ {
		p = prices[i]
		b1 = max(b1, -p)
		s1 = max(s1, p+b1)
		b2 = max(b2, s1-p)
		s2 = max(s2, b2+p)
	}
	return s2

}

func max(nums ...int) int {
	var mx int = MinInt
	for _, num := range nums {
		if num > mx {
			mx = num
		}
	}
	return mx
}

func main() {
	// fmt.Println(maxProfit([]int{3, 3, 5, 0, 0, 3, 1, 4}))
	fmt.Println(maxProfit([]int{6, 1, 3, 2, 4, 7}))
}
