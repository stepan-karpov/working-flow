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
  vll a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  ll ans = -INF;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, a[i]);
  }

  ll cur_s = 0;

  for (int i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      cur_s += a[i];
      ans = max(cur_s, ans);
    }
    if (cur_s < 0) {
      cur_s = 0;
    }
  }

  cur_s = 0;
  
  for (int i = 0; i < n; ++i) {
    if (i % 2 == 1) {
      cur_s += a[i];
      ans = max(cur_s, ans);
    }
    if (cur_s < 0) {
      cur_s = 0;
    }
  }

  cout << ans << "\n";

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  cin >> t;
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