package main

import (
	"fmt"
)

func max(args ...int) int {
	var mx int = args[0]
	var arg int
	for _, arg = range args {
		if arg > mx {
			mx = arg
		}
	}
	return mx
}

/**
 * @param A: A string
 * @param B: A string
 * @return: The length of longest common subsequence of A and B
 */
func longestCommonSubsequence(A string, B string) int {

	var l1, l2 int = len(A), len(B)
	var i, j int
	var dp [][]int = make([][]int, l1+1)

	for i = 0; i < l1+1; i++ {
		dp[i] = make([]int, l2+1)
	}

	for i = 1; i <= l1; i++ {
		for j = 1; j <= l2; j++ {
			if A[i-1] == B[j-1] {
				dp[i][j] = dp[i-1][j-1] + 1
			} else {
				dp[i][j] = max(dp[i-1][j], dp[i][j-1])
			}
		}
	}
	return dp[l1][l2]
}

func main() {
	fmt.Println(longestCommonSubsequence("ABCD", "EACB"))
}
