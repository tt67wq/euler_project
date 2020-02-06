package main

import (
	"fmt"
)

type FreqStack struct {
	freq    map[int]int
	group   map[int][]int
	maxfreq int
}

func Constructor() FreqStack {
	var fs *FreqStack

	fs = new(FreqStack)
	fs.freq = make(map[int]int)
	fs.group = make(map[int][]int)
	fs.maxfreq = 0

	return *fs
}

func (this *FreqStack) Push(x int) {
	var f int

	this.freq[x]++

	f = this.freq[x]

	if f > this.maxfreq {
		this.maxfreq = f
	}

	this.group[f] = append(this.group[f], x)
}

func (this *FreqStack) Pop() int {
	var x, l int

	l = len(this.group[this.maxfreq])
	if l == 0 {
		return 0
	}
	x = this.group[this.maxfreq][l-1]
	this.group[this.maxfreq] = this.group[this.maxfreq][:l-1]
	this.freq[x]--

	if len(this.group[this.maxfreq]) == 0 {
		this.maxfreq--
	}

	return x
}

func main() {}
