#include <algorithm>
#include <iostream>
#include <vector>
#include <future>
#include <chrono>

int square(int x) {
  int time_sleep = 2000;
  std::this_thread::sleep_for(std::chrono::milliseconds(time_sleep));
  return x * x;
}

int main() {
  std::cout << "start\n";
  auto start_time = std::chrono::high_resolution_clock::now();

  std::future<int> asyncFunction1 = std::async(&square, 1);
  std::future<int> asyncFunction2 = std::async(&square, 2);
  std::future<int> asyncFunction3 = std::async(&square, 3);

  int result1 = asyncFunction1.get();
  int result2 = asyncFunction2.get();
  int result3 = asyncFunction3.get();

  std::cout << result1 << "\n";
  std::cout << result2 << "\n";
  std::cout << result3 << "\n";

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "Execution time: " << duration.count() << " milliseconds\n";
  return 0;
}