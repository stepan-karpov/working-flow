package main

import (
	"mainModule/program_examples"
)

func main() {
	sh := program_examples.Rectangle{Width: 5, Height: 6}

	program_examples.PrintShapeDetails(sh)

}
