#include <iostream>
#include <vector>
using std::vector;

void Unsync() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios::sync_with_stdio(false);
}

int main() {
  int n;
  int mod = 1e9 + 7;
  std::cin >> n;
  vector<int> a(n + 1);

  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  
  vector<int> dp(n + 2, 0);
  vector<int> lastins(1000, n + 1);

  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    dp[i] = 2 * dp[i - 1] % mod;
    int l = lastins[a[i]];
    dp[i] = (dp[i] - dp[lastins[a[i]]] + mod) % mod;
    lastins[a[i]] = i - 1;
  }
  std::cout << (dp[n] - 1 + mod) % mod;
}