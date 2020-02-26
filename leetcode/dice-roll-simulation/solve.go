package main

import (
	"fmt"
)

const MOD int = 1000000007
const S int = 15
const A int = 6 * S

func dieSimulator(n int, rollMax []int) int {
	var dp [][]int
	var i, j, k, e, r, ans int

	dp = make([][]int, n+1)
	for i = 0; i <= n; i++ {
		dp[i] = make([]int, A)
	}

	for i = 0; i < 6; i++ {
		dp[1][i*S] = 1
	}

	for i = 2; i <= n; i++ {
		for j = 0; j < A; j++ {
			if dp[i-1][j] > 0 {
				e = j / S
				r = j%S + 1 // 连续重复次数
				if r < rollMax[e] {
					// 未到连续上限
					dp[i][j+1] += dp[i-1][j]
					if dp[i][j+1] >= MOD {
						dp[i][j+1] %= MOD
					}
					for k = 0; k < 6; k++ {
						if k != e {
							dp[i][k*S] += dp[i-1][j]
							if dp[i][k*S] >= MOD {
								dp[i][k*S] %= MOD
							}
						}
					}
				} else {
					// 到达连续上限
					for k = 0; k < 6; k++ {
						if k != e {
							dp[i][k*S] += dp[i-1][j]
							if dp[i][k*S] >= MOD {
								dp[i][k*S] %= MOD
							}
						}
					}
				}
			}
		}
		fmt.Println(dp[i])
	}

	for i = 0; i < A; i++ {
		ans += dp[n][i]
		if ans >= MOD {
			ans %= MOD
		}
	}

	return ans
}

func main() {
	fmt.Println(dieSimulator(30, []int{2, 3, 1, 2, 1, 2}))
	// fmt.Println(dieSimulator(3, []int{1, 1, 1, 2, 2, 3}))
	// fmt.Println(dieSimulator(2, []int{1, 1, 2, 2, 2, 3}))
}
