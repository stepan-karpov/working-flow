#include <iostream>
#include <vector>

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native") // Enable AVX/AVX2
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("rename-registers") // Optimization flags

using std::cout;
using std::cin;

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const int MAX_VALUE = (1e8) / 8;
int answers[MAX_VALUE];
long long p;

int getValue(int i) {
  if (i < MAX_VALUE && answers[i] != 0) {
    return answers[i];
  }
  int v = getValue(p % i);
  int ans = p - (v * (p / i)) % p;
  if (i < MAX_VALUE) {
    answers[i] = ans;
  }
  return ans;
}

int main() {
  Init();
  cin >> p;
  answers[1] = 1;
  long long cur_sum = 1;
  int counter = 1;

  for (int i = 2; i < p / 8; ++i) {
    ++counter;
    answers[i] = (p - (answers[p % i] * (p / i)) % p) % p;
    cur_sum += answers[i];
    if (counter == 100) {
      counter = 0;
      std::cout << cur_sum % p << '\n';
      cur_sum = 0;
    }
  }
  for (int i = std::max(2ll, p / 8); i < p; ++i) {
    ++counter;
    cur_sum += getValue(i);
    if (counter == 100) {
      counter = 0;
      std::cout << cur_sum % p << '\n';
      cur_sum = 0;
    }
  }
  if (counter != 0) {
    std::cout << cur_sum % p << '\n';
  }

  return 0;
}