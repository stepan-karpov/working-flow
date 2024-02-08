package program_examples

import (
	"fmt"
)

func FunctionExample(printValue string) {
	fmt.Println("hello " + printValue)
}

func GCD(a int, b int) int {
	if (b == 0) { return a }
	return GCD(b, a % b);
}

func Division (a int, b int) (int, int) {
	return a / b, a % b;
}