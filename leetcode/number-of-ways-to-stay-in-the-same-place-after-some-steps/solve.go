package main

import (
	"fmt"
)

const M = 1000000007

func numWays(steps int, arrLen int) int {
	var dp1 []int = make([]int, steps+1) // dp1[i] -> 在恰好执行 steps 次操作以后，指针仍然指向索引 i 处的方案数
	var dp2 []int = make([]int, steps+1)
	var i, j int

	dp1[0] = 1

	for i = 0; i < steps; i++ {
		for j = 0; j <= i+1 && j < arrLen; j++ {
			dp2[j] += dp1[j] // 原地不动
			dp2[j] %= M
			if j >= 1 { // 右移
				dp2[j] += dp1[j-1]
				dp2[j] %= M
			}
			if j < arrLen-1 && j <= i { // 左移
				dp2[j] += dp1[j+1]
				dp2[j] %= M
			}
		}
		copy_and_clear(dp1, dp2, steps+1)

	}
	return dp1[0]
}

func copy_and_clear(desc, sour []int, l int) {
	var i int
	for i = 0; i < l; i++ {
		desc[i] = sour[i]
		sour[i] = 0
	}
}

func main() {
	fmt.Println(numWays(3, 2))
}
