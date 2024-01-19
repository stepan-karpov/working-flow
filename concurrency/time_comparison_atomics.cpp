#include <iostream>
#include <thread> 
#include <chrono>
#include <mutex>
#include <vector>

std::atomic<int> x = 0;

void thread1() {
  for (int i = 0; i < 1e8; ++i) {
    x += 1;
  }
}

void thread2() {
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