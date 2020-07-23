package main

const MaxUint = ^uint(0)
const MinUint = 0
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

func min(nums ...int) int {
	var m int = MaxInt
	for _, num := range nums {
		if m > num {
			m = num
		}
	}
	return m
}

func max(nums ...int) int {
	var m int = MinInt
	for _, num := range nums {
		if m < num {
			m = num
		}
	}
	return m
}

func maximalRectangle(matrix [][]byte) int {
	if len(matrix) == 0 {
		return 0
	}
	var ans int = 0
	var dp [][]int = make([][]int, len(matrix))
	for i := 0; i < len(dp); i++ {
		dp[i] = make([]int, len(matrix[i]))
	}

	for i := 0; i < len(matrix); i++ {
		for j := 0; j < len(matrix[i]); j++ {
			if matrix[i][j] == '0' {
				continue
			}

			if j > 0 {
				dp[i][j] = dp[i][j-1] + 1
			} else {
				dp[i][j] = 1
			}

			var width int = dp[i][j]
			for k := i; k >= 0; k-- {
				width = min(width, dp[k][j])
				ans = max(ans, width*(i-k+1))
			}
		}
	}

	return ans
}

func main() {}
