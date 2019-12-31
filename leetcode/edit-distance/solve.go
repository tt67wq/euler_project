package main

import (
	"fmt"
)

func min(nums ...int) int {
	var dqh int
	dqh = 100000
	for _, num := range nums {
		if dqh > num {
			dqh = num
		}
	}
	return dqh
}

func minDistance(word1 string, word2 string) int {

	var dp [][]int = make([][]int, len(word1)+1)
	var i, j int

	for i, _ = range dp {
		dp[i] = make([]int, len(word2)+1)
	}

	// dp[i][j] -> 从 word1前i个字符 到 word2前j个字符 所需要的最少操作数量

	// 插入一个字符
	// 删除一个字符
	// 替换一个字符

	for i = 0; i <= len(word2); i++ {
		dp[0][i] = i
	}

	for j = 0; j <= len(word1); j++ {
		dp[j][0] = j
	}

	for i = 1; i <= len(word1); i++ {
		for j = 1; j <= len(word2); j++ {
			if word1[i-1] == word2[j-1] {
				// 相同
				dp[i][j] = dp[i-1][j-1]
			} else {
				// 不同 需要增删改
				// 比较 dp[i][j-1] dp[i-1][j] dp[i-1][j-1]
				dp[i][j] = min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1

			}
		}
	}
	// fmt.Println(dp)
	return dp[len(word1)][len(word2)]
}

func main() {
	fmt.Println(minDistance("horse", "ros"))
	fmt.Println(minDistance("intention", "execution"))
}
