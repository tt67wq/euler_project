package main

import (
	"fmt"
)

func removeOuterParentheses(S string) string {
	var l, r, i int
	var tmp []byte
	var boxs [][]byte
	var ans string

	tmp = make([]byte, 0)
	boxs = make([][]byte, 0)

	for i = 0; i < len(S); i++ {
		if S[i] == '(' {
			l++
		} else {
			r++
		}

		tmp = append(tmp, S[i])
		if l == r && l > 0 {
			// first time match
			boxs = append(boxs, tmp)
			tmp = make([]byte, 0)
			l, r = 0, 0

		}

	}

	for i = 0; i < len(boxs); i++ {
		boxs[i] = boxs[i][1 : len(boxs[i])-1]
		// fmt.Println(boxs[i])
		ans += string(boxs[i])
	}

	return ans
}

func main() {
	fmt.Println(removeOuterParentheses("(()())(())"))
}
