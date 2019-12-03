package main

import (
	"fmt"
)

/**
 * @param letters: a list of sorted characters
 * @param target: a target letter
 * @return: the smallest element in the list that is larger than the given target
 */
func nextGreatestLetter(letters string, target byte) byte {

	var ls []byte = []byte(letters)
	var e byte

	for _, e = range ls {
		if e > target {
			return e
		}
	}
	if ls[0] == target {
		return ls[1]
	}
	return ls[0]
}

func main() {
	fmt.Println(string(nextGreatestLetter("cfj", 'g')))
}
