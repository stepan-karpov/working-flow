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
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll FindHeight(ll osn, ll s) {
  return (s - 1) / osn + 1;
}

ll TernarySearch(ll s) {
  ll l = 0;
  ll r = 2e18;

  while (r - l > 2) {
    ll m1 = l + (r - l) / 3;
    ll m2 = r - (r - l) / 3;
    
    ll h1 = FindHeight(m1, s);
    ll h2 = FindHeight(m2, s);

    if (m1 + h1 < m2 + h2) {
      r = m2;
    } else {
      l = m1;
    }
  }

  ll min_value = 1e18;
  ll ans = l;

  for (int i = -10; i <= 10; ++i) {
    if (l + i <= 0) {
      continue;
    }
    ll h = FindHeight(l + i, s);
    if (h + l + i < min_value) {
      min_value = h + l + i;
      ans = l + i;
    }
  }

  return ans;
}

void Solve() {
  ll s; cin >> s;
  if (s == 0) {
    cout << "0\n";
    return;
  }
  ll osn = TernarySearch(s);

  std::cout << osn + FindHeight(osn, s) << "\n";

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