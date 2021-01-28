package main

import "fmt"

func isMatch(s string, p string) bool {
	var ss []byte = []byte(s)
	var ps []byte = []byte(p)

	// dp[i][j] -> match?(s[0:i), p[0:j))
	var dp [][]bool = make([][]bool, len(ss)+1)

	for i := 0; i <= len(ss); i++ {
		dp[i] = make([]bool, len(ps)+1)
	}

	// init
	dp[0][0] = true

	if len(ps) > 0 && ps[0] == '*' {
		for i := 0; i <= len(ss); i++ {
			dp[i][1] = true
		}
	}

	for i := 0; i < len(ps); i++ {
		if ps[i] == '*' {
			dp[0][i+1] = dp[0][i]
		}
	}

	for i := 0; i < len(ss); i++ {
		for j := 0; j < len(ps); j++ {
			if ps[j] == '?' {
				dp[i+1][j+1] = dp[i][j]
			} else if ps[j] == '*' {
				for k := 0; k <= i+1; k++ {
					if dp[k][j] {
						for m := k; m <= len(ss); m++ {
							dp[m][j+1] = true
						}
						break
					}
				}
			} else {
				if ps[j] == ss[i] {
					dp[i+1][j+1] = dp[i][j]
				}
			}
		}
	}

	return dp[len(ss)][len(ps)]
}

func main() {
	fmt.Println(isMatch("", ""))
	fmt.Println(isMatch("abc", "*abc?*"))
	fmt.Println(isMatch("aa", "a"))
	fmt.Println(isMatch("aa", "*"))
	fmt.Println(isMatch("cb", "?a"))
	fmt.Println(isMatch("adceb", "*a*b"))
	fmt.Println(isMatch("acdcb", "a*c?b"))
	fmt.Println(isMatch("", "*****"))
	fmt.Println(isMatch("abcabczzzde", "*abc???de*"))

}
