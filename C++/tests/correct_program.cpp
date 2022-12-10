#include <iostream>
#include <vector>
#include <iomanip>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  
  long long a = 901;
  long long b = 33;
  std::cin >> a >> b;
  a += b;
  std::cout << a << '\n';  
  
  return 0;
}