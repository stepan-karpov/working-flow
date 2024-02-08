package program_examples

import (
	"fmt"
	"time"
)

func TimeComparison() {

	start := time.Now()

	var c = 0

	for i := 0; i < 1e10; i++ {
		c++
	}

	fmt.Println("c = ", c)

	elapsed := time.Since(start)
	fmt.Printf("1e10 incrementations in took %s", elapsed)
}
