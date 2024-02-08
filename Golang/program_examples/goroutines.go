package program_examples

import (
	"fmt"
	"strconv"
	"sync"
	"time"
)

var mutex = sync.Mutex{}
var waitGroup = sync.WaitGroup{}
var databases = []string{"id1", "id2", "id3", "id4", "id5"}
var results = []string{}

func connectToDatabase(i int) {
	start := time.Now()
	// var delay = rand.Float32() * 2000
	var delay = 2000

	time.Sleep(time.Duration(delay) * time.Millisecond)

	mutex.Lock()
	results = append(results, "id"+strconv.Itoa(i))
	mutex.Unlock()

	fmt.Printf("Connected to database id%v, time taken: %v\n", i, time.Since(start))
	waitGroup.Done()
}

func Goroutines() {
	start := time.Now()

	for i := 0; i < 6; i++ {
		waitGroup.Add(1)
		go connectToDatabase(i)
	}

	waitGroup.Wait()

	fmt.Printf("Execution finished, time taken: %v\n", time.Since(start))

	fmt.Println(results)
}
