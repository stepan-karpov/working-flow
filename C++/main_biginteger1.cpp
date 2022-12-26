#include <iostream>
#include <vector>
#include "biginteger1.h"

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Init();
  
  std::cout << "start\n";

  BigInteger temp = 0;
  temp += 1;

  // for (int i = 0; i < 1'000'000; ++i) {
  //   temp += i;
  // }

  // std::cout << "start\n";

  return 0;
}