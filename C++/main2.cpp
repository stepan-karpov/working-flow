#include <iostream>
#include <vector>
#include "string.h"

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  String temp1("b");
  String temp2("ba");
  std::string tmp1 = "b";
  std::string tmp2 = "ba";

  bool t = temp1 < temp2;
  bool t2 = tmp1 < tmp2;

  std::cout << t << '\n';
  std::cout << t2 << '\n';
  
  return 0;
}