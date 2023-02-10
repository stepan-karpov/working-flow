#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void f(int* pn) {
  *pn = 1;
}

int main() {
  Init();
  int n = 2;
  f(&n);
  std::cout << n << "\n";
  return 0;
}