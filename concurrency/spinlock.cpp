#include <atomic>

class SpinLock {
private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // Spin until the lock is acquired
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

#include <iostream>
#include <thread>

SpinLock spinlock;

void increment_counter(int &counter) {
    for (int i = 0; i < 100000; ++i) {
        spinlock.lock();
        counter++;
        spinlock.unlock();
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
