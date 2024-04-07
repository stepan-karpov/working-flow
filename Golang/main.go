package main

import (
	"sync"
	"fmt"
)

type ConcurrencyChecker struct {
	mu        sync.Mutex
	nextStage int
	waitCount int
	barrier   chan struct{}
}

func (c *ConcurrencyChecker) Sequential(stage int) {
	fmt.Println("Sequential(%d)", stage)

	c.mu.Lock()
	defer c.mu.Unlock()

	if stage != c.nextStage {
		fmt.Println("testing method is executed out of sequence: expected=%d, got=%d", c.nextStage, stage)
		return
	}
	c.nextStage++
}

func (c *ConcurrencyChecker) Parallel(stage, count int) {
	fmt.Println("Parallel(%d, %d)", stage, count)

	var barrier chan struct{}

	func() {
		c.mu.Lock()
		defer c.mu.Unlock()

		if stage != c.nextStage {
			fmt.Println("testing method is executed out of sequence: expected=%d, got=%d", c.nextStage, stage)
			return
		}

		if c.waitCount == 0 {
			c.barrier = make(chan struct{})
		}
		barrier = c.barrier

		c.waitCount++

		if c.waitCount == count {
			c.waitCount = 0
			c.nextStage++
			close(c.barrier)
		}
	}()

	<-barrier
}

func (c *ConcurrencyChecker) Finish(total int) {
	if total != c.nextStage {
		fmt.Println("wrong number of stages executed: expected=%d, got=%d", total, c.nextStage)
	}
}

type MainSync struct {
	globalMutex  *sync.Mutex
	cv           *sync.Cond
	totalCounter int
	maxCounter   int
}

type T struct {
	myPrettySync  *MainSync
	wasParallel 	bool
	inSubtest 	  bool
}

func (t *T) Parallel() {
	t.wasParallel = true
	t.myPrettySync.totalCounter++
	if t.myPrettySync.totalCounter == t.myPrettySync.maxCounter {
		t.myPrettySync.cv.Broadcast()
		t.myPrettySync.globalMutex.Unlock()
	} else {
		t.myPrettySync.cv.Wait()
		t.myPrettySync.globalMutex.Unlock()
	}
}

func (t *T) Run(subtest func(t *T)) {
	t.myPrettySync.maxCounter++
	subtest(t)
}

func Run(topTests []func(t *T)) {
	mainMutex := sync.Mutex{}
	myPrettySync := MainSync{
		globalMutex:  &mainMutex,
		cv:           sync.NewCond(&mainMutex),
		totalCounter: 0,
		maxCounter:   len(topTests),
	}

	syncChannel := make(chan struct{}, 1)
	syncChannel <- struct{}{}

	tests := make([]T, len(topTests))
	for i := range tests {
		tests[i] = T{myPrettySync: &myPrettySync, wasParallel: false, inSubtest: false}
	}

	var wg sync.WaitGroup
	for i, test := range topTests {
		wg.Add(1)
		go func() {
			<-syncChannel
			myPrettySync.globalMutex.Lock()
			test(&tests[i])
			myPrettySync.totalCounter++
			if myPrettySync.totalCounter == len(topTests) {
				myPrettySync.cv.Broadcast()
			}
			if !tests[i].wasParallel {
				myPrettySync.globalMutex.Unlock()
			}
			wg.Done()
		}()
		syncChannel <- struct{}{}
	}
	wg.Wait()
}


func main() {
	check := &ConcurrencyChecker{}
	defer check.Finish(17)

	Run([]func(*T){
		func(t *T) {
			check.Sequential(0)
		},
		func(t *T) {
			check.Sequential(1)

			t.Run(func(t *T) {
				check.Sequential(2)

				for i := 0; i < 10; i++ {
					t.Run(func(t *T) {
						check.Sequential(3 + i)

						t.Parallel()

						check.Parallel(14, 10)
					})
				}

				check.Sequential(13)
			})

			check.Sequential(15)
		},
		func(t *T) {
			check.Sequential(16)
		},
	})
}