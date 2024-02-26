#include <iostream>
#include <thread> 
#include <chrono>
#include <mutex>
#include <vector>

struct BankAccount {
  BankAccount() = default;
  ~BankAccount() = default;
  std::mutex mtx;
  std::condition_variable cond;

  void thread1(long long& balance) { /* add money */
    std::unique_lock<std::mutex> lock(this->mtx);
    balance += 500;
    std::cout << "Some money added! Current balance is: " << balance << "\n";
    cond.notify_one(); /* cond.notify_all(); */
  }

  void thread2(long long& balance) { /* withdraw money */
    std::unique_lock<std::mutex> lock(this->mtx);
    while (balance < 500) {
      cond.wait(lock, [&balance]() { return balance >= 500; });
    }

    if (balance < 500) { /* protection anyway */
      std::cout << "Not enough money! ";
    } else {
      balance -= 500;
    }
    std::cout << "Current balance is: " << balance << "\n";
  }
};

int main() {
  BankAccount account{};
  
  long long balance = 0;

  std::vector<std::thread> threads;
  // threads.push_back(std::thread(&BankAccount::thread2, &account, std::ref(balance)));
  threads.push_back(std::thread(&BankAccount::thread2, &account, std::ref(balance)));
  threads.push_back(std::thread(&BankAccount::thread1, &account, std::ref(balance)));


  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i].join();
  }
}