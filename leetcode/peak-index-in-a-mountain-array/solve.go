package main

import (
	"fmt"
)

func peakIndexInMountainArray(A []int) int {
	if len(A) == 1 {
		return 0
	}
	var i int

	for i = 1; i < len(A); i++ {
		// 上坡
		if A[i] > A[i-1] {

		} else {
			break
		}
	}
	return i - 1

}

func main() {
	fmt.Println(peakIndexInMountainArray([]int{0, 2, 1, 0}))
}
