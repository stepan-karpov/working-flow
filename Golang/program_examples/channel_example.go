package program_examples

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func CheckPrice(market string, ch chan string, foundMatch *bool,
	waitGroup *sync.WaitGroup, mutex *sync.Mutex) {
	for {
		mutex.Lock()
		if *foundMatch {
			mutex.Unlock()
			break
		} else {
			mutex.Unlock()
		}
		time.Sleep(time.Duration(1) * time.Second)
		var price = rand.Intn(10)
		fmt.Printf("Current price in %v: %v\n", market, price)
		if price >= 9 {
			mutex.Lock()
			*foundMatch = true
			mutex.Unlock()
			ch <- market
			break
		}
	}
	waitGroup.Done()
	fmt.Printf("Monitoring stopped %v\n", market)
}

func SendMessage(ch chan string) {
	fmt.Println(<-ch)
}

func CheckForPrices() {
	foundMatch := false
	var mutex = sync.Mutex{}
	var waitGroup = sync.WaitGroup{}
	var markets = []string{"marketplace.com", "mysales.org", "haha.ru"}
	var ch = make(chan string)

	for i := range markets {
		waitGroup.Add(1)
		go CheckPrice(markets[i], ch, &foundMatch, &waitGroup, &mutex)
	}
	SendMessage(ch)

	waitGroup.Wait()

	fmt.Println("program exit")
}
