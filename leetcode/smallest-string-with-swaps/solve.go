package main

import (
	"fmt"
)

type dset struct {
	root int
	size int
}

func new_set(capacity int) []*dset {
	var res []*dset
	var i int

	res = make([]*dset, capacity)
	for i = 0; i < capacity; i++ {
		res[i] = new(dset)
		res[i].root = -1
		res[i].size = 0
	}
	return res
}

func find(s []*dset, k int) *dset {
	if s[k].root == -1 {
		// new
		s[k].root = k
		s[k].size = 1
		return s[k]
	}
	var tmp *dset

	tmp = s[k]
	for tmp.root != k {
		k = tmp.root
		tmp = s[k]
	}
	s[k].root = tmp.root
	return s[k]
}

func set_union(s []*dset, m, n int) {
	var mr, nr *dset

	mr = find(s, m)
	nr = find(s, n)

	if mr.size <= nr.size {
		s[mr.root].root = nr.root
		s[nr.root].size += mr.size
	} else {
		s[nr.root].root = mr.root
		s[mr.root].size += nr.size
	}
}

func in_slice(ns []int, m int) bool {
	for _, n := range ns {
		if m == n {
			return true
		}
	}
	return false
}

func sort_by_idx(s *string, ps []int) {
	var b []byte
	var i, j int
	var t byte

	b = []byte(*s)

	for i = 0; i < len(ps)-1; i++ {
		for j = i + 1; j < len(ps); j++ {
			if b[ps[i]] > b[ps[j]] {
				t = b[ps[i]]
				b[ps[i]] = b[ps[j]]
				b[ps[j]] = t
			}
		}
	}
	*s = string(b)
}

func quick_sort(nums []int, begin, end int) {
	var i, j, t int

	if begin < end {
		i = begin + 1
		j = end
		for i < j {
			if nums[i] > nums[begin] {
				// swap
				t = nums[i]
				nums[i] = nums[j]
				nums[j] = t
				j--
			} else {
				i++
			}
		}

		if nums[i] >= nums[begin] {
			i--
		}

		t = nums[i]
		nums[i] = nums[begin]
		nums[begin] = t

		quick_sort(nums, begin, i)
		quick_sort(nums, j, end)
	}
}

func smallestStringWithSwaps(s string, pairs [][]int) string {
	var ds []*dset
	var i, j int
	var ps []int
	var mp map[int][]int

	ds = new_set(100000)
	mp = make(map[int][]int)

	for i = 0; i < len(pairs); i++ {
		set_union(ds, pairs[i][0], pairs[i][1])
	}

	for i = 0; i < len(pairs); i++ {
		j = find(ds, pairs[i][0]).root
		if !in_slice(mp[j], pairs[i][0]) {
			mp[j] = append(mp[j], pairs[i][0])
		}

		j = find(ds, pairs[i][1]).root
		if !in_slice(mp[j], pairs[i][1]) {
			mp[j] = append(mp[j], pairs[i][1])
		}

	}

	for _, ps = range mp {
		if len(ps) > 1 {
			quick_sort(ps, 0, len(ps)-1)
			sort_by_idx(&s, ps)
		}
	}
	return s
}

func main() {
	//
	// []
	var a string = "zbxxxdgmbz"
	fmt.Println(smallestStringWithSwaps(a, [][]int{{1, 0}, {7, 1}, {9, 1}, {3, 0}, {7, 1}, {0, 4}, {6, 5}, {2, 6}, {6, 4}, {6, 0}}))

}
