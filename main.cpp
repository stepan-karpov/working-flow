#include <algorithm>
#include <iostream>
#include <vector>

namespace constants {
  const long long kMod = 1'000'000'007;
}

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

bool MaskCanOccur(int mask, const std::vector<std::string>& table, int column, int n) {
  // mask >> 0       == table[0]
  //        ...
  // mask >> (n - 1) == table[0]
  for (int i = 0; i < n; ++i) {
    bool mybit123 = ((mask >> i) & 1) != 0;
    if (mybit123 && table[i][column] == '+') {
      return false;
    }
    if (!mybit123 && table[i][column] == '-') {
      return false;
    }
  }
  return true;
}

int RestoreMask(int mask, int first, int n) {
  int old_mask = first;
  for (int i = 1; i < n; ++i) {
    int last = (old_mask >> (i - 1)) & 1;
    int t1 = (mask >> (i - 1)) & 1;
    int t2 = (mask >> i) & 1;
    int new_s = 2 - last - t1 - t2;
    if (new_s == 1) {
      old_mask |= (1 << i);
    }
  }
  return old_mask;
}

bool Match(int mask1, int mask2, int n) {
  for (int i = 0; i < n - 1; ++i) {
    int t1 = (mask1 >> i) & 1;
    int t2 = (mask1 >> (i + 1)) & 1;
    int t3 = (mask2 >> i) & 1;
    int t4 = (mask2 >> (i + 1)) & 1;
    if (t1 + t2 + t3 + t4 != 2) {
      return false;
    }
  }
  return true;
}

int main() {
  Init();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> table(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> table[i];
  }

  int maximum_mask = (1 << n);

  std::vector<std::vector<long long>> dp(
      m + 1, std::vector<long long>(maximum_mask, 0));

  for (int mask = 0; mask < maximum_mask; ++mask) {
    if (MaskCanOccur(mask, table, 0, n)) {
      dp[1][mask] = 1;
    }
  }

  for (int i = 2; i <= m; ++i) {
    for (int mask = 0; mask < maximum_mask; ++mask) {
      if (!MaskCanOccur(mask, table, i - 1, n)) {
        continue;
      }
      int old_mask1 = RestoreMask(mask, 0, n);
      int old_mask2 = RestoreMask(mask, 1, n);
      if (MaskCanOccur(old_mask1, table, i - 2, n) && Match(mask, old_mask1, n)) {
        dp[i][mask] += dp[i - 1][old_mask1];
      }
      if (MaskCanOccur(old_mask2, table, i - 2, n) && Match(mask, old_mask2, n)) {
        dp[i][mask] += dp[i - 1][old_mask2];
      }
      dp[i][mask] %= constants::kMod;
    }
  }

  long long answer = 0;

  for (int mask = 0; mask < maximum_mask; ++mask) {
    if (MaskCanOccur(mask, table, m - 1, n)) {
      answer += dp[m][mask];
      answer %= constants::kMod;
    }
  }

  std::cout << answer << "\n";

  return 0;
}