#include <algorithm>
#include <iostream>
#include <vector>

using std::cout, std::endl;

std::string Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}



int main() {

  if constexpr (std::is_same_v<void, decltype(Init)>) {
    std::cout << "func is void\n";
  } else if constexpr (std::is_same_v<int, decltype(Init())>){
    std::cout << "func is int\n";
  } else {
    std::cout << "func is jopa\n";
  }

  return 0;
}