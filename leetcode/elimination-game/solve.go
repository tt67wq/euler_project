package main

import (
	"fmt"
)

func A(n int) int {
	if n == 1 {
		return 1
	} else {
		return 2 * B(n/2)
	}
}

func B(n int) int {
	if n == 1 {
		return 1
	} else {
		if n%2 == 0 {
			return 2*A(n/2) - 1
		} else {
			return 2 * A(n/2)
		}
	}
}

func lastRemaining(n int) int {
	return A(n)
}

func main() {
	var n int
	for {
		fmt.Scanln(&n)
		fmt.Println(lastRemaining(n))
	}

}
