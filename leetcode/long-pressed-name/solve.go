package main

import (
	"fmt"
)

func isLongPressedName(name string, typed string) bool {
	var i, j, x, y int
	var a byte

	for i < len(name) {
		x = 0
		y = 0
		a = name[i]

		for i < len(name) && name[i] == a {
			i++
			x++
		}
		for j < len(typed) && typed[j] == a {
			j++
			y++
		}

		if y < x {
			return false
		}
	}
	return true
}

func main() {
	fmt.Println(isLongPressedName("saeed", "ssaaedd"))
	fmt.Println(isLongPressedName("leelee", "lleeelee"))
}
