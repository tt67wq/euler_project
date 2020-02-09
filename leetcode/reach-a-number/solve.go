package main

import (
	"fmt"
)

func reachNumber(target int) int {
	if target == 0 {
		return 0
	}
	var acc, i int

	acc = 0
	i = 1
	if target < 0 {
		target = -target
	}

	for {
		acc += i
		if acc >= target && (acc-target)%2 == 0 {
			return i
		}
		i++
	}

}

func main() {
	var n int
	for {
		fmt.Scanf("%d", &n)
		fmt.Println(reachNumber(n))
	}

}
