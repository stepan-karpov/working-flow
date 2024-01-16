#include <iostream>
#include <thread> 
#include <chrono>
#include <mutex>
#include <vector>

std::mutex mtx;

void thread1(int& total) {
  std::cout << "welcome to thread " << std::this_thread::get_id() << "\n";

  std::lock_guard<std::mutex> guard(mtx);
  for (int i = 0; i < 100000; ++i) {
    ++total;
  }

  std::cout << "bye from thread " << std::this_thread::get_id() << "\n";
}

void thread2(int& total) {
  std::cout << "welcome to thread " << std::this_thread::get_id() << "\n";

  std::lock_guard<std::mutex> guard(mtx);
  for (int i = 0; i < 100000; ++i) {
    ++total;
  }


  std::cout << "bye from thread " << std::this_thread::get_id() << "\n";
}

int main() {
  int total = 0;

  std::vector<std::thread> threads;
 
  threads.push_back(std::thread(thread1, std::ref(total)));
  threads.push_back(std::thread(thread2, std::ref(total)));

  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i].join();
  }

  std::cout << total << "\n";
}