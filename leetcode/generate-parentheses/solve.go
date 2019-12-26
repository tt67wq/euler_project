package main

import (
	"fmt"
)

func generateParenthesis(n int) []string {
	var array []int = make([]int, 2*n)
	var ans []string = make([]string, 0)

	perm(0, 2*n, n, n, array, &ans)
	return ans
}

func perm(deep, n, lc, rc int, array []int, ans *[]string) {
	if deep == n {
		// finish
		var res string
		for _, m := range array {
			if m == 0 {
				res += "("
			} else {
				res += ")"
			}
		}
		*ans = append(*ans, res)
		return
	}

	// must lc >= rc
	if lc == rc {
		array[deep] = 0
		perm(deep+1, n, lc-1, rc, array, ans)
	} else if lc < rc {
		if lc > 0 {
			array[deep] = 0
			perm(deep+1, n, lc-1, rc, array, ans)
		}

		array[deep] = 1
		perm(deep+1, n, lc, rc-1, array, ans)
	} else {
		return
	}

}

func main() {
	var array []int = make([]int, 6)
	var ans []string = make([]string, 0)
	perm(0, 6, 3, 3, array, &ans)
	fmt.Println(ans)
}
