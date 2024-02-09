package program_examples

import "fmt"

func SumSlice[T int | float32 | string](slice []T) T {
	var sum T
	for _, v := range slice {
		sum += v
	}
	return sum
}

func Generics() {
	var IntSlice = []int{1, 2, 3, 4}
	var FloatSlice = []float32{1.0, 2.5, 3.7, 4.23}
	var StringSlice = []string{"aa", "bb", "cc"}

	fmt.Println(SumSlice[int](IntSlice))
	fmt.Println(SumSlice[float32](FloatSlice))
	fmt.Println(SumSlice[string](StringSlice))
}
