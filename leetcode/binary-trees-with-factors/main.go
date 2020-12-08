package main

import (
	"fmt"
	"sort"
)

const mod int64 = 1000000007

func numFactoredBinaryTrees(A []int) int {
	var l int = len(A)
	sort.Slice(A, func(i, j int) bool { return A[i] < A[j] })

	var dp []int64 = make([]int64, l)
	for i := 0; i < l; i++ {
		dp[i] = 1
	}

	var vis map[int]int = make(map[int]int)

	for i := 0; i < l; i++ {
		vis[A[i]] = i
	}

	for i := 0; i < l; i++ {
		for j := 0; j < i; j++ {
			if A[i]%A[j] == 0 {
				d := A[i] / A[j]
				if v, ok := vis[d]; ok {
					dp[i] += (dp[j] * dp[v])
					dp[i] %= mod
				}
			}
		}
	}

	var ans int64 = 0
	for i := 0; i < l; i++ {
		ans += dp[i]
		ans %= mod
	}
	return int(ans)
}

func main() {
	fmt.Println(numFactoredBinaryTrees([]int{2, 4, 5, 10}))
}
