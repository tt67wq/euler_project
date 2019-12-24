package main

import (
	"fmt"
)

func minDeletionSize(A []string) int {
	if len(A) <= 1 {
		return 0
	}

	var l, w, ans, i, j int
	var rise bool

	l = len(A)
	w = len(A[0])
	ans = 0

	for i = 0; i < w; i++ {
		rise = true
		for j = 1; j < l; j++ {
			// if down, escape
			if A[j][i] < A[j-1][i] {
				rise = false
				break
			}
		}
		if !rise {
			ans++
		}
	}

	return ans

}

func main() {
	fmt.Println(minDeletionSize([]string{"cba", "daf", "ghi"}))
	fmt.Println(minDeletionSize([]string{"a", "b"}))
	fmt.Println(minDeletionSize([]string{"zyx", "wvu", "tsr"}))
}
