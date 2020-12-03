package main

import (
	"fmt"
	"sort"
)

type car struct {
	pos      int
	speed    int
	timeCost float32
}

func carFleet(target int, position []int, speed []int) int {

	var carNum int = len(position)
	if carNum == 0 {
		return 0
	}
	var cars []*car = make([]*car, carNum)

	for i := 0; i < carNum; i++ {
		cars[i] = new(car)
		cars[i].pos = position[i]
		cars[i].speed = speed[i]
		cars[i].timeCost = float32(target-position[i]) / float32(speed[i])
	}

	// sort
	sort.Slice(cars, func(i, j int) bool { return cars[i].pos > cars[j].pos })

	for i := 0; i < carNum; i++ {
		fmt.Println(*cars[i])
	}

	var res int = 1
	for i := 0; i+1 < carNum; i++ {
		if cars[i].timeCost < cars[i+1].timeCost {
			res++
		} else {
			cars[i+1].timeCost = cars[i].timeCost
		}
	}
	return res
}

func main() {
	fmt.Println(carFleet(10, []int{0, 4, 2}, []int{2, 1, 3}))
}
