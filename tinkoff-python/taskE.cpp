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

void Solve() {
  ll n; cin >> n;
  vll a(n);

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vll b(n + 1);

  b[0] = 0;
  b[1] = a[0];

  for (int i = 1; i < n; ++i) {
    b[i + 1] = b[i] + a[i];
  }

  map<ll, set<ll>> coord;

  for (int i = 0; i <= n; ++i) {
    coord[b[i]].insert(i);
  }

  vll next_v(n + 1, -1);

  for (int i = 0; i <= n; ++i) {
    if (coord[b[i]].lower_bound(i + 1) != coord[b[i]].end()) {
      next_v[i] = *coord[b[i]].lower_bound(i + 1);
    }
  }

  ll ans = 0;

  vll dp(n + 1, -1);

  for (int i = n - 1; i >= 0; --i) {
    if (dp[i + 1] == -1 && next_v[i] == -1) {
      continue;
    } else if (dp[i + 1] == -1 && next_v[i] != -1) {
      dp[i] = next_v[i];
      ans += n - dp[i] + 1 ;
    } else if (dp[i + 1] != -1 && next_v[i] == -1) {
      dp[i] = dp[i + 1];
      ans += n - dp[i] + 1;
    } else if (dp[i + 1] != -1 && next_v[i] != -1) {
      dp[i] = min(dp[i + 1], next_v[i]);
      ans += n - dp[i] + 1;
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
    Solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}