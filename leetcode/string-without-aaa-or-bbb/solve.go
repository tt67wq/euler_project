package main

import (
	"fmt"
)

func strWithout3a3b(A int, B int) string {
	var s []byte
	var a, b byte
	var k int

	s = make([]byte, A+B)
	a = 'a'
	b = 'b'
	k = 0

	if A < B {
		A, B = B, A
		a, b = b, a
	}

	// 先aab 不满足就ab
	for A > 0 || B > 0 {
		if A > 0 {
			s[k] = a
			A--
			k++
		}
		if A > B {
			s[k] = a
			A--
			k++
		}
		if B > 0 {
			s[k] = b
			B--
			k++
		}
	}
	return string(s)

}

func main() {
	fmt.Println(strWithout3a3b(4, 1))
}
