#include <iostream>
#include <vector>
#include <algorithm>

const long long kMod = 998'244'353;
const long long SIZE = 1100;

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Init();
  
  long long n = 0;
  long long m = 0;
  std::cin >> n >> m;
  std::vector<long long> p(n + 1);
  std::vector<long long> q(m + 1);
  for (long long i = 0; i <= n; ++i) {
    std::cin >> p[i];
  }
  for (long long i = 0; i <= m; ++i) {
    std::cin >> q[i];
  }
  while (p.size() != SIZE) {
    p.push_back(0);
  }
  while (q.size() != SIZE) {
    q.push_back(0);
  }

  std::vector<long long> sum;

  for (long long i = 0; i < SIZE; ++i) {
    sum.push_back((p[i] + q[i]) % kMod);  
  }
  while (!sum.empty() && sum[sum.size() - 1] == 0) {
    sum.pop_back();
  }
  std::vector<long long> mult(SIZE);
  
  for (long long i = 0; i < SIZE; ++i) {
    for (long long j = 0; j <= i; ++j) {
      mult[i] += p[j] * q[i - j];
      mult[i] %= kMod;
    }
  }
  while (!mult.empty() && mult[mult.size() - 1] == 0) {
    mult.pop_back();
  }

  int ZERO = 0;
  int s1 = sum.size() - 1;
  int s2 = mult.size() - 1;

  std::cout << std::max(ZERO, s1) << '\n';
  for (long long i = 0; i < sum.size(); ++i) {
    std::cout << sum[i] << ' ';
  }
  std::cout << '\n';

  std::cout << std::max(ZERO, s2) << '\n';
  for (long long i = 0; i < mult.size(); ++i) {
    std::cout << mult[i] << ' ';
  }
  std::cout << '\n';

  std::vector<long long> div(SIZE + 1);
  div[0] = p[0] % kMod;

  for (long long i = 1; i < 1000; ++i) {
    div[i] = p[i] + kMod;
    for (int j = i - 1; j >= 0; --j) {
      long long delta = div[j] * q[i - j];
      delta %= kMod;
      div[i] -= delta;
      div[i] = (div[i] + 2 * kMod) % kMod;
    }
  }

  for (int i = 0; i < 1000; ++i) {
    std::cout << div[i] << ' ';
  }
  std::cout << '\n';

  return 0;
}