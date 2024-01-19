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

int x = 0;
std::mutex mtx;

void thread1() {
  std::unique_lock lock(mtx);
  for (int i = 0; i < 1e8; ++i) {
    x += 1;
  }
}

void thread2() {
  std::unique_lock lock(mtx);
  for (int i = 0; i < 1e8; ++i) {
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