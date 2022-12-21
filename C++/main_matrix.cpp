#include <iostream>
#include <vector>
#include "matrix.h"

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

using std::vector;

int main() {
  Init();


  Matrix<4, 4> m;

  std::cout << m.getValue(1, 2) << '\n';

  return 0;
}