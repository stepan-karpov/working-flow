#include <iostream>
#include <vector>
#include "string.h"

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  String temp1("abc");
  String temp2("def");

  // (temp1 += temp2) += temp2;
  temp1 += temp2 += temp2;

  std::cout << temp1 << '\n';
  
  return 0;
}