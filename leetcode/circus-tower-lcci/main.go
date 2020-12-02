package main

import "sort"

type person struct {
	height int
	weight int
}

func bestSeqAtIndex(height []int, weight []int) int {

	var num int = len(height)
	var personList []*person = make([]*person, num)

	for i := 0; i < num; i++ {
		personList[i] = new(person)
		personList[i].height = height[i]
		personList[i].weight = weight[i]
	}

	// sort by weight desc
	sort.SliceStable(personList, func(i, j int) bool { return personList[i].weight > personList[j].weight })

	// sort by height asc
	sort.SliceStable(personList, func(i, j int) bool { return personList[i].height < personList[j].height })

	var dp []int

	for i := 0; i < num; i++ {
		if len(dp) == 0 || personList[dp[len(dp)-1]].height < personList[i].height && personList[dp[len(dp)-1]].weight < personList[i].weight {
			dp = append(dp, i)
		} else {
			l, r := 0, len(dp)-1

			// binSearch
			for l < r {
				mid := (l + r) >> 1
				if personList[dp[mid]].height < personList[i].height && personList[dp[mid]].weight < personList[i].weight {
					l = mid + 1
				} else {
					r = mid
				}
			}
			dp[r] = i
		}
	}

	return len(dp)
}

func main() {}
