package main

import (
	"fmt"
)

func isValid(S string) bool {

	if S == "" {
		return true
	}
	var i, l int

	l = len(S)

	for i = 0; i+2 < l; i++ {
		if S[i:i+3] == "abc" {
			break
		}
	}
	if i == l-2 {
		return false
	}
	return isValid(S[0:i] + S[i+3:])
}

func main() {
	fmt.Println(isValid("aabcbc"))
	fmt.Println(isValid("abcabcababcc"))
	fmt.Println(isValid("abccba"))
	fmt.Println(isValid("cababc"))
}
