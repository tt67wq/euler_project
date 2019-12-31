package main

import (
	"fmt"
)

func longestCommonPrefix(strs []string) string {

	var l, idx int = len(strs), 0
	var i int
	var ans string
	if l == 0 {
		ans = ""
		return ans
	}
	if l == 1 {
		ans = strs[0]
		return ans
	}

	for idx = 0; idx < len(strs[0]); idx++ {
		fgz := strs[0][idx]
		for i = 1; i < l; i++ {
			if len(strs[i]) <= idx {
				break
			}
			if strs[i][idx] != fgz {
				break
			}
		}
		if i == l {
			ans += string(fgz)
		} else {
			break
		}
	}
	return ans
}

func main() {
	fmt.Println(longestCommonPrefix([]string{"flower", "flow", "flight"}))
	fmt.Println(longestCommonPrefix([]string{"dog", "racecar", "car"}))
	fmt.Println(longestCommonPrefix([]string{"aaa", "aa", "a"}))
}
