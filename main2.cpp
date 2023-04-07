#include <algorithm>
#include <iostream>
#include <vector>


void foo(int* n) {
  *n = 123;
}

int main() {
  int n;

  foo(&n);

  std::cout << n << "\n";
  
  return 0;
}