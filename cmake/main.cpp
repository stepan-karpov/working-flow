#include <iostream>
#include "include/print.hpp"

int main() {
  std::cout << "Hello world" << "\n";
  std::string temp = "anc";
  print(temp);
  std::cout << temp << "\n";
  return 0;
}