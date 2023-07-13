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

void check(string& s, ll n, ll m, ll& p) {
  for (int i = 0; i < s.size(); ++i) {
    ll neig_right = i + 1;
    ll neigh_down = i + n;
    ll c = 0;
    if (neig_right < s.size() && s[neig_right] == s[i]) {
      s[neig_right] = ALPH[p];
      ++c;
    }
    if (neigh_down < s.size() && s[neigh_down] == s[i]) {
      s[neigh_down] = ALPH[p];
      ++c;
    }
    p += c;
  }
}

void solve() {
  ll n; cin >> n;
  ll p = 1;
  string ans;
  ans.assign(n, 'a');

  for (int i = 1; i <= sqrt(n) + 10; ++i) {
    if (n % i == 0) {
      check(ans, n / i, i, p);
      check(ans, i, n / i, p);
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