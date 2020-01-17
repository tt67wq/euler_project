package main

import (
	"fmt"
)

func max(nums ...int) int {
	var m int
	m = -1
	for _, num := range nums {
		if num > m {
			m = num
		}
	}
	return m
}

func view_dp(dp [][]int) {
	var i, j int

	for i = 0; i < len(dp); i++ {
		for j = 0; j < len(dp[0]); j++ {
			fmt.Print(dp[i][j], "\t")
		}
		fmt.Print("\n")
	}
}

func superEggDrop(K int, N int) int {

	var i, j, k, m, t int
	var dp [][]int // dp[i][j] -> 用i个蛋确定j层楼所用次数

	dp = make([][]int, K+1)

	for i = 0; i <= K; i++ {
		dp[i] = make([]int, N+1)
	}

	for j = 0; j <= N; j++ {
		dp[1][j] = j // 一个蛋只能挨个试验
	}

	for i = 1; i <= K; i++ {
		dp[i][0] = 0
		dp[i][1] = 1
	}

	for i = 2; i <= K; i++ {
		for j = 2; j <= N; j++ {
			// 假设第一蛋从k层投下
			m = 10000
			for k = 1; k*2 <= 1+j; k++ {
				t = max(dp[i-1][k-1], dp[i][j-k])
				if t == dp[i][j-1]-1 {
					m = t
					break
				} else if t < m {
					m = t
				}
			}
			dp[i][j] = m + 1

		}
	}
	view_dp(dp)
	return dp[K][N]
}

func main() {
	var K, N int
	for {
		fmt.Scanf("%d %d", &K, &N)
		fmt.Println(superEggDrop(K, N))
	}
}
