package main

import (
	"fmt"
)

func matrixReshape(nums [][]int, r int, c int) [][]int {
	if len(nums) == 0 {
		return [][]int{}
	}
	var r0, c0, i, j, k int
	var ns []int
	var ans [][]int

	r0 = len(nums)
	c0 = len(nums[0])

	if r0*c0 != r*c {
		return nums
	}
	ans = make([][]int, r)
	for i = 0; i < r; i++ {
		ans[i] = make([]int, c)
	}

	ns = make([]int, r*c)

	// resharp
	k = 0
	for i = 0; i < r0; i++ {
		for j = 0; j < c0; j++ {
			ns[k] = nums[i][j]
			k++
		}
	}

	k = 0
	for i = 0; i < r; i++ {
		for j = 0; j < c; j++ {
			ans[i][j] = ns[k]
			k++
		}
	}
	return ans

}

func main() {
	fmt.Println(matrixReshape([][]int{{1, 2}, {3, 4}}, 1, 4))
}
