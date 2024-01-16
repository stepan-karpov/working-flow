#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

void DoWork(std::promise<int>&& promise) {
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  promise.set_value(1);
}

int main() {
  int answer = 0;

  std::promise<int> promise;
  std::future<int> value = promise.get_future();

  std::cout << "value of answer is: " << answer << "\n";

  std::thread thread(DoWork, std::move(promise));

  std::cout << "Waiting for result\n";
  answer = value.get();
  std::cout << "value of answer is: " << answer << "\n";

  thread.join();
}