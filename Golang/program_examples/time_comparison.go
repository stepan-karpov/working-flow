package program_examples

import (
	"fmt"
	"time"
)

func TimeComparison() {

	start := time.Now()

	var c = 0

	for i := 0; i < 1e11; i++ {
		c++
	}

	fmt.Println("c = ", c)

	elapsed := time.Since(start)
	fmt.Printf("Binomial took %s", elapsed)
}
