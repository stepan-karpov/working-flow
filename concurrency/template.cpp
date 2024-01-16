#include <iostream>
#include <thread> 
#include <chrono>
#include <mutex>
#include <vector>

void thread1() {
  std::cout << "welcome to thread " << std::this_thread::get_id() << "\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(950));
  std::cout << "bye from thread " << std::this_thread::get_id() << "\n";
}

void thread2() {
  std::cout << "welcome to thread " << std::this_thread::get_id() << "\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "bye from thread " << std::this_thread::get_id() << "\n";
}

int main() {

  std::vector<std::thread> threads;

  threads.push_back(std::thread(thread1));
  threads.push_back(std::thread(thread2));

  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i].join();
  }
}