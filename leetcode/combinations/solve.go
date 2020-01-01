package main

import (
	"fmt"
)

func do_combine(n, m, deep int, res, vis []int, ans *[][]int) {
	if deep == m {
		var tmp []int = make([]int, m)
		copy(tmp, res)
		*ans = append(*ans, tmp)
		return
	}

	var i int

	for i = 1; i <= n; i++ {
		if vis[i] == 0 {
			if deep > 0 {
				if res[deep-1] < i {
					vis[i] = 1
					res[deep] = i
					do_combine(n, m, deep+1, res, vis, ans)
					vis[i] = 0
				}
			} else {
				vis[i] = 1
				res[deep] = i
				do_combine(n, m, deep+1, res, vis, ans)
				vis[i] = 0
			}
		}
	}
}

func combine(n int, k int) [][]int {
	var res, vis []int = make([]int, k), make([]int, n+1)
	var ans [][]int = make([][]int, 0)
	do_combine(n, k, 0, res, vis, &ans)
	return ans
}

func main() {
	fmt.Println(combine(4, 2))
}
