package main

import (
	"fmt"
)

func in_slice(uhd []int, ws4 int) bool {
	for _, e0c := range uhd {
		if ws4 == e0c {
			return true
		}
	}
	return false
}

func in_slice2(uhd [][]int, ws4 []int) bool {
	for _, e0c := range uhd {
		if ws4[0] == e0c[0] && ws4[1] == e0c[1] {
			return true
		}
	}
	return false
}

// 小镇的法官不相信任何人。
// 每个人（除了小镇法官外）都信任小镇的法官。
// 只有一个人同时满足属性 1 和属性 2 。
func findJudge(N int, trust [][]int) int {
	if N == 1 && len(trust) == 0 {
		return 1
	}
	var i int
	var notJudge []int = make([]int, 0)
	var probablyJudge []int = make([]int, 0)

	for i = 0; i < len(trust); i++ {
		notJudge = append(notJudge, trust[i][0])
	}
	for i = 0; i < len(trust); i++ {
		if in_slice(notJudge, trust[i][1]) {
			// pass
		} else {
			if !in_slice(probablyJudge, trust[i][1]) {
				probablyJudge = append(probablyJudge, trust[i][1])
			}

		}
	}

	// 小镇的法官不相信任何人 pass

	if len(probablyJudge) != 1 {
		return -1
	}
	// fmt.Println(probablyJudge)

	// 每个人（除了小镇法官外）都信任小镇的法官。
	for i = 1; i <= N; i++ {
		if i == probablyJudge[0] {
			continue
		}
		if !in_slice2(trust, []int{i, probablyJudge[0]}) {
			break
		}
	}
	if i == N+1 {
		return probablyJudge[0]
	}

	return -1
}

func main() {
	fmt.Println(findJudge(1, [][]int{}))
	// fmt.Println(findJudge(2, [][]int{{1, 2}}))
	// fmt.Println(findJudge(3, [][]int{{1, 3}, {2, 3}}))
	// fmt.Println(findJudge(3, [][]int{{1, 3}, {2, 3}, {3, 1}}))
	// fmt.Println(findJudge(3, [][]int{{1, 2}, {2, 3}}))
	// fmt.Println(findJudge(4, [][]int{{1, 3}, {1, 4}, {2, 3}, {2, 4}, {4, 3}}))
}
