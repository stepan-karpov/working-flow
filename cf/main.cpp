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

bool possible(vector<pll> scores, ll time) {
  ll n = scores.size();
  for (int i = 0; i < n; ++i) {
    if (time) 
  }
}

ll binSearch(vector<pll>& scores, ll time) {
  ll l = -1;
  ll r = 1e5 * 5;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (possible(m, scores, time)) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

void solve() {
  ll n, m;
  cin >> n >> m;
  vector<pll> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].second;
    a[i].first = n - i;
  }

  sort(a.begin(), a.end());

  for (int i = 0; i < n; ++i) {
    cout << a[i].first << " " << a[i].second << '\n';
  }

  cout << binSearch(a, m) << '\n';
  
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