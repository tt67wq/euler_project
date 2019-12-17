package main

import (
	"fmt"
)

func numTilings(N int) int {
	if N <= 2 {
		return N
	}
	var dp1 []int = make([]int, N+1)
	var dp2 []int = make([]int, N+1)
	var i int
	var m int = 1000000007

	dp1[1] = 1
	dp1[2] = 2
	dp2[2] = 2

	for i = 3; i <= N; i++ {
		dp1[i] = (dp1[i-1] + dp1[i-2] + dp2[i-1]) % m
		dp2[i] = (dp1[i-2]*2 + dp2[i-1]) % m
	}
	return dp1[N]
}

func main() {
	var N int
	for {
		fmt.Println("Please input N:")
		fmt.Scanln(&N)
		fmt.Println(numTilings(N))
	}
	return
}
