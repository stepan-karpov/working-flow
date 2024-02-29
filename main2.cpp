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

  size_t thread_count = 0;
  
  while (thread_count++ > 0) {
    std::cout << "Here!\n";
    --thread_count;
  }
  return 0;
}