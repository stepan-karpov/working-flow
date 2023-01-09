#include <iostream>
#include <vector>
#include <tuple>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

std::tuple<int, int, int> extendedEuclid(int a, int b) {
  if (a == 0) {
    return {0, 1, b};
  }
  auto[x, y, gcd] = extendedEuclid(b % a, a);
  return {
    y - (b / a) * x,
    x,
    gcd
  };
}

int main() {
  Init();
  int a, b, c;
  std::cin >> a >> b >> c;

  auto[x, y, gcd] = extendedEuclid(a, b);

  if (c % gcd != 0) {
    std::cout << "Impossible" << '\n';
    return 0;
  }

  std::cout << gcd << " " << c / gcd * x << " " << c / gcd * y << '\n';

  return 0;
}