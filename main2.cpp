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

vll z_func(string s) {
  ll n = s.size();
  vll z(n);
  ll l = -1, r = -1;
  for (int i = 1; i < n; ++i) {
    if (l <= i && i <= r) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) { ++z[i]; }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}


void Solve() {
  string s; cin >> s;
  ll n = s.size();

  ll ans = 1;

  for (int i = 0; i < n; ++i) {
    ll new_len = n - i;
    vll z = z_func(s.substr(i, n - i));
    for (int j = i + 1; j < n; ++j) {
      ll potential_period = j - i + 1;
      ll local_k = z[j - i] / potential_period;
      ans = max(ans, local_k + 1);
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