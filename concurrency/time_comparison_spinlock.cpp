#include <iostream>
#include <thread> 
#include <chrono>
#include <mutex>
#include <vector>

/* in this example mutex works faster than std::atomic<int> because
   mutex locks resourses only twice, while std::atomic<int> has to lock
   resources every time. If you put unique_lock inside for loop, the time will
   increase accordingly
*/

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

SpinLock spinlock;

int x = 0;

void thread1() {
  std::unique_lock lock(spinlock);
  for (int i = 0; i < 1e9; ++i) {
    x += 1;
  }
}

void thread2() {
  std::unique_lock lock(spinlock);
  for (int i = 0; i < 1e9; ++i) {
    x += 1;
  }
}
 
int main() {
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  std::vector<std::thread> threads;

  threads.push_back(std::thread(thread1));
  threads.push_back(std::thread(thread2));

  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i].join();
  }
  std::cout << "x = " << x << "\n";
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}