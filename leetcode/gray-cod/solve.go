package main

import (
	"fmt"
	"math"
)

func grayCode(n int) []int {
	var i int
	var ans []int

	ans = make([]int, 0)

	for i = 0; i < int(math.Pow(2, float64(n))); i++ {
		ans = append(ans, i^(i>>1))
	}
	return ans
}

func main() {
	fmt.Println(grayCode(3))
}
