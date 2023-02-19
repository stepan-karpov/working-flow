#include <iostream>

void print(std::string& s) {
  std::cout << s << "\n";
  s[1] = 's';
}