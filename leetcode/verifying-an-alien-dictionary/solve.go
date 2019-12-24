package main

import (
	"fmt"
)

func compare(word1, word2 string, order map[byte]int) int {
	// 0 -> ==
	// 1 -> >
	// 2 -> <
	if word1 == word2 {
		return 0
	}

	var i, j int

	i = 0
	j = 0

	for i < len(word1) && j < len(word2) {
		if order[word1[i]] < order[word2[i]] {
			return 1
		}
		if order[word1[i]] > order[word2[i]] {
			return 2
		}
		i++
		j++

	}

	// shorter one win

	if i == len(word1) {
		return 1
	}

	return 2
}

func isAlienSorted(words []string, order string) bool {

	if len(words) <= 1 {
		return true
	}

	var order_mp map[byte]int = make(map[byte]int)
	var idx int

	// for idx, char = range order {
	// 	order_mp[char] = idx
	// }
	for idx = 0; idx < len(order); idx++ {
		order_mp[order[idx]] = idx
	}

	for idx = 1; idx < len(words); idx++ {
		if compare(words[idx-1], words[idx], order_mp) == 2 {
			return false
		}
	}
	return true
}

func main() {
	fmt.Println(isAlienSorted([]string{"hello", "leetcode"}, "hlabcdefgijkmnopqrstuvwxyz"))
	fmt.Println(isAlienSorted([]string{"word", "world", "row"}, "worldabcefghijkmnpqstuvxyz"))
	fmt.Println(isAlienSorted([]string{"apple", "app"}, "abcdefghijklmnopqrstuvwxyz"))
}
