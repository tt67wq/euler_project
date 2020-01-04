package main

import (
	"fmt"
)

const M = 1000000007

func findPaths(m int, n int, N int, i int, j int) int {

	if N == 0 {
		return 0
	}

	var dp1, dp2 [][]int = make([][]int, m), make([][]int, m)
	var idx, a, b, ans int

	ans = 0
	for idx = 0; idx < m; idx++ {
		dp1[idx] = make([]int, n)
		dp2[idx] = make([]int, n)
	}

	// 1步
	for a = 0; a < m; a++ {
		dp1[a][0] += 1
		dp1[a][n-1] += 1
	}

	for b = 0; b < n; b++ {
		dp1[0][b] += 1
		dp1[m-1][b] += 1
	}
	ans += dp1[i][j]

	for idx = 2; idx < N+1; idx++ {
		// fmt.Println(dp1)
		for a = 0; a < m; a++ {
			for b = 0; b < n; b++ {
				// up
				if a > 0 && dp1[a-1][b] > 0 {
					dp2[a][b] += dp1[a-1][b]
				}
				// down
				if a < m-1 && dp1[a+1][b] > 0 {
					dp2[a][b] += dp1[a+1][b]
				}
				// left
				if b > 0 && dp1[a][b-1] > 0 {
					dp2[a][b] += dp1[a][b-1]
				}
				// right
				if b < n-1 && dp1[a][b+1] > 0 {
					dp2[a][b] += dp1[a][b+1]
				}
				dp2[a][b] %= M
			}
		}

		for a = 0; a < m; a++ {
			for b = 0; b < n; b++ {
				dp1[a][b] = dp2[a][b]
				dp2[a][b] = 0
			}
		}

		ans += dp1[i][j]
		ans %= M

	}
	// fmt.Println(dp1)
	return ans
}

func main() {
	fmt.Println(findPaths(36, 5, 50, 15, 3))
}
