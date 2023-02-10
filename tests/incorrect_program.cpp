#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const long long MOD = 1e9 + 7;

int main() {
  Init();
  
  long long n;
  std::cin >> n;
  std::vector<long long> a(n);
  for (long long i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<long long> dp(n, 0);
  dp[0] = 2;

  for (long long i = 1; i < n; ++i) {
    long long cnt = 0;
    for (long long j = 0; j < i; ++j) {
      if (a[i] == a[j]) {
        ++cnt;
      }
    }
    int not_ends_with_i = i - cnt;
    int ends_with_i = cnt;
    dp[i] = dp[i - 1] * 2 + MOD - cnt - not_ends_with_i;
    dp[i] %= MOD;
  }

  std::cout << dp[n - 1] - 1 << "\n";

  for (int i = 0; i < n; ++i) {
    std::cout << dp[i] << " ";
  }
  std::cout << "\n";

  return 0;
}