package program_examples

import "fmt"

type gasEngine struct {
	fuel         int8
	gallons      int8
	ownerProfile owner
}

type electricEngine struct {
	charge       int8
	accumulators int8
}

type owner struct {
	name string
	id   int8
}

func (e gasEngine) milesLeft() int {
	return int(e.fuel) * int(e.gallons)
}

func (e electricEngine) milesLeft() int {
	return int(e.accumulators) * int(e.charge)
}

func (e gasEngine) canMakeIt(miles int) bool {
	return e.milesLeft() >= miles
}

func (e electricEngine) canMakeIt(miles int) bool {
	return e.milesLeft() >= miles
}

type engine interface {
	canMakeIt() bool
}

func Foo() {
	var engine1 gasEngine
	var engine2 = gasEngine{fuel: 15, gallons: 23, ownerProfile: owner{"Sophie", 4}}
	var engine3 = gasEngine{1, 1, owner{"Alex", 100}}
	var engine4 = electricEngine{15, 18}

	engine1.fuel = 123
	engine1.gallons = 12

	fmt.Println(engine1)
	fmt.Println(engine2)
	fmt.Println(engine3)
	fmt.Println(engine4)

	fmt.Println(engine1.canMakeIt(123))
	fmt.Println(engine2.canMakeIt(123))
	fmt.Println(engine3.canMakeIt(123))
	fmt.Println(engine4.canMakeIt(123))

}
