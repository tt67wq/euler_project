package main

import (
	"fmt"
)

const M = 41000

func minIncrementForUnique(A []int) int {
	var i, j, ans int
	var vis []int
	vis = make([]int, M)

	for _, a := range A {
		vis[a]++
	}

	ans = 0
	for i = 0; i < M; i++ {
		if vis[i] > 1 {
			j = (vis[i] - 1)
			ans += j
			vis[i+1] += j
		}
	}
	return ans
}

func main() {

}
