#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const int kInf = 1e9;
using Pll = std::pair<long long, long long>;

int BinPow(int aa, int xx, int mod) {
  if (xx == 0) {
    return 1;
  }
  if (xx % 2 == 0) {
    long long temp = BinPow(aa, xx / 2, mod);
    return (temp * temp) % mod;
  }
  long long t1 = aa;
  long long t2 = BinPow(aa, xx - 1, mod);
  return (t1 * t2) % mod;
}

Pll RecalcRemainder(Pll rem1, Pll rem2, long long mod, long long aa) {
  long long t1 = rem1.first;
  long long t2 = rem2.first;
  long long r1 = rem1.second;
  long long r2 = rem2.second;

  Pll ans = {0, 0};
  ans.first = (((t1 * r2) % mod) + ((t2 * r1) % mod)) % mod;
  ans.second = ((r1 * r2) % mod + (((t1 * t2) % mod) * aa) % mod) % mod;
  return ans;
}

Pll BinPow2(long long pivot, long long xx, long long aa, long long mod) {
  if (xx == 1) {
    return {1, pivot};
  }
  if (xx % 2 == 0) {
    Pll temp = BinPow2(pivot, xx / 2, aa, mod);
    return RecalcRemainder(temp, temp, mod, aa);
  }
  return RecalcRemainder({1, pivot}, BinPow2(pivot, xx - 1, aa, mod), mod, aa);
}

// returns b, c coefficients
// remainder in (x + i) ^ ((p - 1) / 2) - 1 mod (x^2 - a)
Pll FindRemainder(long long aa, long long pp, long long pivot) {
  auto ans = BinPow2(pivot, (pp - 1) / 2, aa, pp);
  ans.second = (ans.second + pp - 1) % pp;
  return ans;
}

void Solve() {
  long long aa;
  long long pp;
  std::cin >> aa >> pp;

  if (pp == 2 || aa == 0) {
    std::cout << aa << "\n";
    return;
  }
  if (BinPow(aa, (pp - 1) / 2, pp) != 1) {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  for (int i = 0; i < kInf; ++i) {
    int pivot = rand() % (pp - 1) + 1;
    std::pair<long long, long long> rem = FindRemainder(aa, pp, pivot);
    if (rem.first != 0) {
      long long ans = rem.second;
      // std::cout << pivot << ": " << rem.first << " " << rem.second << "\n";
      ans *= BinPow(rem.first, pp - 2, pp);
      ans %= pp;
      if (((ans * ans) % pp) != aa) {
        continue;
      }
      std::cout << ans << "\n";
      return;
    }
  }
}

int main() {
  srand(time(nullptr));
  Init();
  int tests = 1;
  std::cin >> tests;
  for (int i = 0; i < tests; ++i) {
    Solve();
  }
  return 0;
}