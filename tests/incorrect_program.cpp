#include <bits/stdc++.h>
using namespace std;
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,avx,tune=native")
// #pragma GCC optimize("fast-math")
// #pragma GCC optimize(2)
// #pragma GCC optimize("Ofast","inline","-ffast-math")
// #pragma GCC optimize "-O3"

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vb = vector<bool>;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

void solve() {
  ll n, m; cin >> n >> m;
  vvll a(n, vll(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  vvll dp = a;


  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      if (a[i][j] == 0) { continue; }
      ll up_s = dp[i - 1][j];
      ll left_s = dp[i][j - 1];
      ll new_sq = min(up_s, left_s);
      if (a[i - new_sq][j - new_sq] == 1) {
        dp[i][j] = new_sq + 1;
      } else {
        dp[i][j] = new_sq;
      }
    }
  }

  ll ans = -INF;
  pll pos = {0, 0};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (dp[i][j] > ans) {
        ans = dp[i][j];
        pos = {i, j};
      }
    }
  }
  cout << ans << "\n";

  // cout << "\n\n";

  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < m; ++j) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << "\n";
  // }

  cout << pos.first - ans + 2 << " " << pos.second - ans + 2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  // cin >> t;
  // cout << fixed << setprecision(10);
  
  while (t--) {
    solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}