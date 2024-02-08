package program_examples

import "fmt"

func Pointers() {
	var p *int32
	var i int32 = 324567

	p = &i

	fmt.Println(p)
	fmt.Println(*p)
}

func DoubleMemory(Slice [5]float64) {
	fmt.Println(&Slice[0])
}

func SingleMemory(Slice *[5]float64) {
	fmt.Println(&(*Slice)[0])
}

func SlicesPointers() {
	var Slice = [5]float64{1, 2, 3, 4, 5}
	fmt.Println(&Slice[0])
	DoubleMemory(Slice)
	SingleMemory(&Slice)

}
