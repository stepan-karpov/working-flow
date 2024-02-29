#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct A {
  A() {
    std::cout << "Constr\n";
  }

  ~A() {
    std::cout << "Destr\n";
  }
};

int main() {
  Init();

  std::vector<A> vv(4);

  vv.clear();

  std::cout << "sdf\n";


  return 0;
}