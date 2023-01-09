#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

std::vector<long long> extendedGCD(long long a, long long b) {
  if (a == 0) {
    return {0, 1, b};
  }
  std::vector<long long> answer = extendedGCD(b % a, a);
  return {
    answer[1] - (b / a) * answer[0],
    answer[0],
    answer[2]
  };
}

int main() {
  Init();
  long long a, m;
  std::cin >> a >> m;
  if (a == 0) {
    std::cout << "-1" << '\n';
    return 0;
  }

  std::vector<long long> answer = extendedGCD(a, m);

  if (answer[2] != 1) {
    std::cout << "-1" << '\n';
    return 0;
  }
  std::cout << ((answer[0] + m) % m) << '\n';




  return 0;
}