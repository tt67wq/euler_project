package main

import (
	"fmt"
)

func findAnagrams(s string, p string) []int {
	var c1, c2, ans []int
	var i, j int
	var ss, ps []byte

	c1 = make([]int, 26)
	c2 = make([]int, 26)
	ss = []byte(s)
	ps = []byte(p)
	ans = make([]int, 0)

	if len(ss) < len(ps) {
		return ans
	}

	for i = 0; i < len(ps); i++ {
		c2[ps[i]-'a']++
	}

	for i = 0; i < len(ps); i++ {
		c1[ss[i]-'a']++
	}

	j = i
	i = 0
	for j <= len(ss) {
		if cmp(c1, c2) {
			ans = append(ans, i)
		}
		if j < len(ss) {
			c1[ss[i]-'a']--
			c1[ss[j]-'a']++
		}
		i++
		j++
	}
	return ans
}

func cmp(c1, c2 []int) bool {
	var i int

	for i = 0; i < 26; i++ {
		if c1[i] != c2[i] {
			return false
		}
	}
	return true
}

func main() {
	fmt.Println(findAnagrams("abab", "ab"))
}
