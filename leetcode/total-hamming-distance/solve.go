package main

import (
	"fmt"
	"math"
)

const MAX int = 30

func totalHammingDistance(nums []int) int {
	var i, j, l, a, x, y, ans int

	l = len(nums)

	for i = 0; i < MAX; i++ {
		a = int(math.Pow(2, float64(i)))
		x = 0
		y = 0
		for j = 0; j < l; j++ {
			if a&nums[j] == a {
				// 1
				x++
			} else {
				// 0
				y++
			}
		}
		// fmt.Println(i, ":", x, y)
		ans += (x * y)
	}
	return ans
}

func main() {
	fmt.Println(totalHammingDistance([]int{4, 14, 2}))
}
