#include <algorithm>
#include <iostream>
#include <vector>
#include <barrier>
#include <thread>

const int THREADS = 4;

std::barrier sync_barrier(THREADS);

void sleep(int i) {
  int sleep_duration = rand() % 1000;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
  std::string output = "hello world from " + std::to_string(i) + " " + std::to_string(sleep_duration) + "\n"; 
  std::cout << output;
}

void my_function(int i) {
  sleep(i);
  sync_barrier.arrive_and_wait();
  sleep(i);
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < THREADS; ++i) {
    threads.push_back(std::thread(my_function, i));
  }

  for (int i = 0; i < THREADS; ++i) {
    threads[i].join();
  }

  return 0;
}