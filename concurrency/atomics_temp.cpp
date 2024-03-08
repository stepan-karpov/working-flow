#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Init();
  std::atomic<int> t1 = 5;
  std::atomic<int> t2 = 6;

  std::cout << t1.exchange(t2) << "\n";

  return 0;
}