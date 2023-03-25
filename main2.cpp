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

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef long double ld;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll ans = -INF;

void checkBinPow(ll l, ll r, vvll& E, ll sum) {
  if (r - l <= 1) {
    ans = max(ans, sum);
    return;
  }
  ll m = (l + r) / 2;
  checkBinPow(l, m, E, sum + E[l][m - 1]);
  checkBinPow(m, r, E, sum + E[l][m - 1]);

}

void solve() {
  ll n; cin >> n;
  vvll E(n, vll(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - i; ++j) {
      cin >> E[i][j];
    }
  }

  checkBinPow(0, n, E, E[0][n - 1]);

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