package main

import "fmt"

func geneGreyCode(n int) []string {
	base := []string{"0", "1"}

	idx := 1
	for idx < n {
		tmp := []string{}
		for i := 0; i < len(base); i++ {
			tmp = append(tmp, "0"+base[i])
		}
		for i := len(base) - 1; i >= 0; i-- {
			tmp = append(tmp, "1"+base[i])
		}
		idx++
		base = tmp
	}
	return base
}

func binStrToInt(s string) int {
	runes := []rune(s)
	n := 0
	for _, r := range runes {
		if r == 48 {
			n *= 2
		} else {
			n *= 2
			n++
		}
	}
	return n
}

func circularPermutation(n int, start int) []int {
	greyCode := geneGreyCode(n)

	nums := []int{}
	for _, code := range greyCode {
		nums = append(nums, binStrToInt(code))
	}

	// rotate it
	idx := 0
	for i := 0; i < len(nums); i++ {
		if nums[i] == start {
			idx = i
			break
		}
	}

	return append(nums[idx:], nums[:idx]...)
}

func main() {

	fmt.Println(circularPermutation(3, 2))
}
