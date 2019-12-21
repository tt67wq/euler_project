package main

import (
	"fmt"
	"math"
	"strconv"
)

func Reverse(s string) string {
	runes := []rune(s)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}

func largestPalindrome(n int) int {
	var upper, lower, i, j, tg int
	var tmp string

	upper = int(math.Pow10(n)) - 1
	lower = int(math.Pow10(n - 1))

	for i = upper; i >= lower; i-- {
		// target palindrome
		tmp = strconv.Itoa(i)
		tg, _ = strconv.Atoi(tmp + Reverse(tmp))

		fmt.Println(tg)
		// assume j is bigger factor
		for j = upper; j*j >= tg; j-- {
			if tg%j == 0 {
				return tg % 1337
			}
		}
	}
	return 9
}

func main() {
	fmt.Println(largestPalindrome(2))
}
