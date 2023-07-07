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

bool CanBe(vvll& a, ll i, ll j, ll max_r) {
  for (int dx = 0; dx < max_r; ++dx) {
    for (int dy = 0; dy < max_r; ++dy) {
      if (a[i + dx][j + dy] == 0) { return false; }
    }
  }
  return true;
}

ll Count(vvll& a, ll i, ll j) {
  ll n = a.size();
  ll m = a[0].size();

  ll max_r = min(n - i, m - j);

  ll ans = 0;

  for (ll r = 0; r <= max_r; ++r) {
    if (CanBe(a, i, j, r)) {
      ans = max(ans, r);
    }
  }
  return ans;
}

void solve() {
  ll n, m; cin >> n >> m;
  vvll a(n, vll(m, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }

  ll ans = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ans = max(ans, Count(a, i, j));
    }
  }
  cout << ans << "\n";
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