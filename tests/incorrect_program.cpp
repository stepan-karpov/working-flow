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
  ll n; cin >> n;
  vll a;
  ll last = -1;
  for (int i = 0; i < n; ++i) {
    ll x; cin >> x;
    if (x == 0) {
      a.push_back(x);
    } else if (x != last) {
      a.push_back(x);
    }
    last = x;
  }

  n = a.size();

  vll dp(n + 10, INF);
  dp[0] = 0;

  for (int i = 1; i <= n; ++i) {
    dp[i] = min(dp[i], dp[i - 1] + 1);
    ll cur_v = a[i - 1];
    if (cur_v == 1) {
      if (i - 2 >= 0) {
        dp[i] = min(dp[i], dp[i - 2] + 1);
      }
    } else if (cur_v == 2) {
      if (i - 2 >= 0) {
        dp[i] = min(dp[i], dp[i - 2] + 1);
      }
      ll d = 1;
      if (i - 2 >= 0) {
        d = dp[i - 2] + 1;
      }
      dp[i + 1] = min(dp[i + 1], d);
    }
  }

  cout << dp[n] << "\n";
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