package main

import "fmt"

func zeller(day int, month int, year int) int {
	c := year / 100
	y := year % 100
	m := month
	if m < 3 {
		m += 12
		year--
		c = year / 100
		y = year % 100
	}
	r := c/4 - 2*c + y + y/4 + 13*(m+1)/5 + day - 1
	for r < 0 {
		r += 7
	}
	return r
}

func dayOfTheWeek(day int, month int, year int) string {
	var weekdays []string = []string{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
	// fmt.Println("D =", zeller(day, month, year))
	return weekdays[zeller(day, month, year)%7]
}

func main() {
	fmt.Println(dayOfTheWeek(31, 8, 2019))
	fmt.Println(dayOfTheWeek(13, 12, 1994))
	fmt.Println(dayOfTheWeek(18, 7, 1999))
	fmt.Println(dayOfTheWeek(15, 8, 1993))
	fmt.Println(dayOfTheWeek(29, 2, 2016))
}
