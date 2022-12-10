#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const long long MOD = 998244353;

long long BinPow(long long a, long long x) {
  if (x == 0) {
    return 1;
  }
  if (x % 2 == 0) {
    long long t = BinPow(a, x / 2);
    return (t * t) % MOD;
  }
  return (a * BinPow(a, x - 1)) % MOD;
}

int main() {
  Init();
  long long n;
  std::cin >> n;
  if (n == 1) {
    std::cout << "0\n";
    return 0;
  }

  long long answer = 0;

  answer += BinPow(3, n - 1);
  answer -= BinPow(-1, n - 1);
  answer += MOD;
  answer *= 3;
  answer %= MOD;
  answer *= BinPow(4, MOD - 2);
  answer %= MOD;

  std::cout << answer << '\n';

  return 0;
}