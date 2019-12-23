package main

import (
	"fmt"
	"strings"
)

func uncommonFromSentences(A string, B string) []string {
	var AB, ts string
	var mp map[string]int = make(map[string]int)
	var c int
	var ans []string = make([]string, 0)

	AB = A + " " + B

	for _, ts = range strings.Split(AB, " ") {
		mp[ts] += 1
	}

	for ts, c = range mp {
		if c == 1 {
			ans = append(ans, ts)
		}
	}
	return ans
}

func main() {
	fmt.Println(uncommonFromSentences("this apple is sweet", "this apple is sour"))
}
