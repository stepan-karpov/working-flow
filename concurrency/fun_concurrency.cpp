#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>

std::mutex mutex_;
int cnt = 0;

void function() {
  mutex_.lock();
  for (int i = 0; i < 1e9; ++i) {
    ++cnt;
  }
  mutex_.unlock();
}

int main() {
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  std::vector<std::thread> threads;

  threads.push_back(std::thread(function));
  threads.push_back(std::thread(function));

  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i].join();
  }

  std::cout << cnt << "\n";


  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  return 0;
}