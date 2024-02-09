package program_examples

import (
	"fmt"
	"math/rand"
	"time"
)

func SingleProc(ch chan int) {
	defer close(ch)
	var cnt = rand.Intn(5) + 3
	for i := 0; i < cnt; i++ {
		var value = rand.Intn(10)
		ch <- value
	}
}

func SingleChannel() {
	var ch = make(chan int)

	go SingleProc(ch)

	for i := range ch {
		fmt.Println(i)
	}
}

func MultipleProc(ch chan int) {
	defer close(ch)
	for i := 0; i < 5; i++ {
		ch <- i
	}
	fmt.Println("Exiting function")
}

func MultipleChannel() {
	var ch = make(chan int, 5)

	go MultipleProc(ch)

	for i := range ch {
		fmt.Println(i)
		time.Sleep(time.Duration(1) * time.Second)
	}
}
