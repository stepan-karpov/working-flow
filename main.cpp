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

ll Calc(string s) {
  ll ans = 0;
  for (ll i = 1; i < s.size() - 1; ++i) {
    ll start2 = s.size() - i;
    string s1 = s.substr(0, i);
    string s2 = s.substr(start2, i);
    if (s1 == s2) {
      ans = max(ans, i);
    }
  }
  return ans;
}

void solve() {
  ll ans = 0;
  ll best_l = 0, best_r = 0;
  string s; cin >> s;
  for (int l = 0; l < s.size(); ++l) {
    for (int r = l; r < s.size(); ++r) {
      int temp = Calc(s.substr(l, r - l + 1));
      int res = r - l + 1 + temp * temp;
      if (res > ans) {
        ans = res;
        best_l = l;
        best_r = r;
      }
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