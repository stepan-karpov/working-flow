package program_examples

import (
	"fmt"
	"time"
)

func ArraysFunction() {
	s := 1
	s = 1e17
	fmt.Println(&s)

	var intArray [3]int32

	intArray[0] = 1
	intArray[1] = 2
	intArray[2] = 3

	fmt.Println(intArray[0] + intArray[1] + intArray[2])
	fmt.Println(&intArray)
	fmt.Println(intArray)
	fmt.Println(&intArray[0])
	fmt.Println(&intArray[1])
	fmt.Println(&intArray[2])
}

func Slices() {
	var Slice = []int32{1, 2, 3}

	fmt.Println(Slice)
	fmt.Println(&Slice[0])
	fmt.Println(cap(Slice))

	Slice = append(Slice, 123)

	fmt.Println(Slice)
	fmt.Println(&Slice[0])
	fmt.Println(cap(Slice))

	var Slice2 = []int32{45, 56, 57, 67}

	Slice = append(Slice, Slice2...)

	fmt.Println(Slice)
	fmt.Println(&Slice[0])
	fmt.Println(cap(Slice))

	Slice = append(Slice, Slice2...)

	fmt.Println(Slice)
	fmt.Println(&Slice[0])
	fmt.Println(cap(Slice))

	for i, v := range Slice {
		fmt.Println(i, v, ";")
	}
}

func Maps() {
	var Map = make(map[string]int32)

	Map["gosha"] = 10
	Map["stepa"] = 19

	fmt.Println(Map)

	age, ok := Map["alice"]

	if ok {
		fmt.Println("Age is ", age)
	} else {
		fmt.Println("Aboba")
	}

	delete(Map, "stepa")

	fmt.Println(Map)

	Map["haha"] = 123
	Map["gaga"] = 34
	Map["dsf"] = 335

	for key, value := range Map {
		fmt.Println("Key, value =", key, ",", value)
	}
}

func PushBackMillionTimes(Slice []int32, border int) {
	start := time.Now()
	for i := 0; i < border; i++ {
		Slice = append(Slice, 0)
	}
	fmt.Println("Time spent:", time.Since(start))
}

func SlicesExperiment() {
	const border = int(1e9)

	var Slice1 = make([]int32, 0, border)
	var Slice2 = make([]int32, 0, 0)

	PushBackMillionTimes(Slice1, border)
	PushBackMillionTimes(Slice2, border)
}
