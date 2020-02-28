package main

import (
	"fmt"
)

const MaxUint = ^uint(0)
const MinUint = 0
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

func abs(n int) int {
	if n < 0 {
		return -n
	}
	return n
}

func min(nums ...int) int {
	var m int = MaxInt
	for _, num := range nums {
		if num < m {
			m = num
		}
	}
	return m
}

func distance(a, b int) int {
	var xa, ya, xb, yb int

	xa = a / 6
	ya = a % 6
	xb = b / 6
	yb = b % 6

	return abs(xa-xb) + abs(ya-yb)
}

// CAKE
func minimumDistance(word string) int {
	var l, i, j, k, c, p, d, d0, ans int
	var dp [][][]int // dp[i][l][r] -> 表示在输入了字符串 word 的第 i 个字母后，左手的位置为 l，右手的位置为 r，达到该状态的最小移动距离

	l = len(word)

	dp = make([][][]int, l)

	for i = 0; i < l; i++ {
		dp[i] = make([][]int, 26)
		for j = 0; j < 26; j++ {
			dp[i][j] = make([]int, 26)
			for k = 0; k < 26; k++ {
				dp[i][j][k] = MaxInt
			}
		}
	}

	for i = 0; i < 26; i++ {
		dp[0][word[0]-'A'][i] = 0 // 左手在0
		dp[0][i][word[0]-'A'] = 0 // 右手在0
	}

	for i = 1; i < l; i++ {
		// from p to c
		c = int(word[i] - 'A')
		p = int(word[i-1] - 'A')
		d = distance(c, p)

		// p c 都在一只手的情况
		for j = 0; j < 26; j++ {
			dp[i][c][j] = min(dp[i][c][j], dp[i-1][p][j]+d) // left: p -> c
			dp[i][j][c] = min(dp[i][j][c], dp[i-1][j][p]+d) // right: p -> c

		}

		// p c 在两只手分开的情况
		// left: p, right: c | right: p, left: c
		for k = 0; k < 26; k++ {
			d0 = distance(k, c)
			dp[i][c][p] = min(dp[i][c][p], dp[i-1][k][p]+d0) // left: k -> c
			dp[i][p][c] = min(dp[i][p][c], dp[i-1][p][k]+d0) // right: k -> c
		}
	}

	ans = MaxInt
	for i = 0; i < 26; i++ {
		j = min(dp[l-1][i]...)
		if j < ans {
			ans = j
		}
	}

	return ans

}

func main() {
	fmt.Println(minimumDistance("CAKE"))
	fmt.Println(minimumDistance("HAPPY"))
}
