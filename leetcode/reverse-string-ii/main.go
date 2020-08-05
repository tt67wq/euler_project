package main

import "fmt"

func _reverseBetween(s string, from, to int) string {
	runes := []rune(s)
	for i, j := from, to-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}

func reverseStr(s string, k int) string {
	var i0, j0, j1 int
	i0 = 0
	j0 = 0
	j1 = 0

	var l int = len(s)
	var flag bool = false

	for {
		if flag {
			break
		}
		for d := 0; d < k; d++ {
			i0++
			if i0 > l {
				i0 = l
			}
			j0 += 2
			if j0 > l {
				j0 = l
				flag = true
			}
		}

		s = _reverseBetween(s, j1, i0)
		// fmt.Println(j1, i0, s)
		i0 = j0
		j1 = j0
	}

	return s
}

func main() {
	fmt.Println(reverseStr("abcdefg", 2))
}
