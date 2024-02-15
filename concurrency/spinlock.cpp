#include <iostream>
#include <thread>
#include <atomic>

class SpinLock {
 public:
  void Lock() {
    while (thread_count_.fetch_add(1) > 0) {
      thread_count_.fetch_sub(1);  // Step back
    }
  }

  void Unlock() {
    thread_count_.fetch_sub(1);
  }

 private:
  std::atomic<size_t> thread_count_{0};
};

SpinLock spinlock;

void increment_counter(int &counter) {
    for (int i = 0; i < 100000; ++i) {
        spinlock.Lock();
        counter++;
        spinlock.Unlock();
    }
}

int main() {
    int counter = 0;

    std::thread t1(increment_counter, std::ref(counter));
    std::thread t2(increment_counter, std::ref(counter));

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl;

    return 0;
}
