#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const long long kMod = 1e9 + 7;

int main() {
  Init();
  long long n;
  std::cin >> n;

  std::vector<long long> last_entry(1e6 + 1, -1);
  std::vector<long long> a(n + 1);
  std::vector<long long> dp(n + 1, 0);

  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }

  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    dp[i] = 2 * dp[i - 1];
    if (last_entry[a[i]] != -1) {
      dp[i] -= dp[last_entry[a[i]]];
      dp[i] = (dp[i] + kMod) % kMod;
    }
    last_entry[a[i]] = i - 1;
  }

  std::cout << (dp[n] + kMod - 1) % kMod << "\n";

  return 0;
}