package main

import (
	"fmt"
)

func countSegments(s string) int {
	var i, ans int

	s += " "
	for i = 0; i < len(s); i++ {
		if s[i] != ' ' && s[i+1] == ' ' {
			ans++
		}
	}
	return ans
}

func main() {
	fmt.Println(countSegments(", , , , a, eaefa"))
	fmt.Println(countSegments("Hello, my name is John"))
}
