package main

// 并查集
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
	}
	return res
}

func find(s []*dset, k int) *dset {
	if s[k].root == 0 {
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

func main() {
	var s []*dset

	s = new_set(1000)
	find(s, 10)
	find(s, 20)
	set_union(s, 10, 20)
	find(s, 30)
	find(s, 30)
	set_union(s, 30, 10)
	fmt.Println(find(s, 30).root)
}
