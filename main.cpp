#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

bool VertexInMask(int mask, int u) { return (((mask >> u) & 1) != 0); }

int main() {
  Init();
  int n;
  std::cin >> n;

  std::vector<std::string> a(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> dp((1 << n), 0);

  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int u = 0; u < n; ++u) {
      if (!VertexInMask(mask, u)) {
        continue;
      }
      for (int v = 0; v < n; ++v) {
        if (!VertexInMask(mask, v) || u == v) {
          continue;
        }
        if (a[u][v] == 'N') {
          continue;
        }
        int new_mask = mask;
        new_mask ^= (1 << u);
        new_mask ^= (1 << v);
        int new_value = dp[new_mask] + 2;
        dp[mask] = std::max(dp[mask], new_value);
      }
    }
  }

  std::cout << dp[(1 << n) - 1] << "\n";

  return 0;
}