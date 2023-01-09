#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Init();
  long long temp1 = 998'244'353;

  std::cout << temp1 * temp1 << '\n';

  return 0;
}