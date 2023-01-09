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
  long long a, b, c;
  std::cin >> a >> b >> c;

  std::vector<long long> answer = extendedGCD(a, b);
  long long gcd = answer[2];
  long long x = answer[0] * c / gcd;
  long long y = answer[1] * c / gcd;

  if (c % gcd != 0) {
    std::cout << "Impossible";
    return 0;
  }

  long long k = (-x * gcd) / b;
  long long new_x = x + k * (b / gcd);
  long long new_y = y - (k + 1) * (a / gcd);
  
  if (new_x < 0) {
    new_x = x + (k + 1) * (b / gcd);
  } else {
    new_y = y - k * (a / gcd);
  }
  std::cout << new_x << ' ' << new_y;
}
