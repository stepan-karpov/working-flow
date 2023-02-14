#include <bits/stdc++.h>
using namespace std;

void Unsync() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios::sync_with_stdio(false);
}

void Solve(int m, int n, vector<int> a) {
  vector<int> ans = {1000000000, -1, -1};
  vector<int> pref(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    pref[i] = a[i] + pref[i - 1];
  }
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 1000000000));
  vector<vector<int>> prev(m + 1, vector<int>(n + 1, -1));
  for (int i = 1; i <= n; ++i) {
    dp[1][i] = (a[i] * i - pref[i]) + (pref[n] - pref[i] - (n - i) * a[i]);
    ans = min(ans, {dp[1][i], 1, i});
  }
  for (int q = 2; q <= m; ++q) {
    for (int i = q; i <= n; ++i) {
      for (int j = i - 1; j >= 1; --j) {
        int mid = (a[i] + a[j]) / 2;
        int midx = (upper_bound(a.begin(), a.end(), mid) - a.begin());
        int s0 = (pref[n] - pref[midx - 1]) - (n - midx + 1) * a[j];
        int s3n = (pref[n] - pref[i - 1]) - (n - i + 1) * a[i];
        int s2n = (i - midx + 1) * a[i] - (pref[i] - pref[midx - 1]);
        int curp = dp[q - 1][j] - s0 + s3n + s2n;
        if (dp[q][i] > curp) {
          prev[q][i] = j;
          dp[q][i] = curp;
          ans = min(ans, {dp[q][i], q, i});
        }
      }
    }
  }
  cout << ans[0] << "\n";
  vector<int> path;
  while (ans[2] != -1) {
    path.push_back(a[ans[2]]);
    ans[2] = prev[ans[1]][ans[2]];
    --ans[1];
  }
  sort(path.begin(), path.end());
  for (int i : path) {
    cout << i << " ";
  }
}

int main() {
  Unsync();
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  Solve(m, n, a);
}