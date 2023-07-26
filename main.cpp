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

void output(pll ans, vll& a, ll k) {
  ll p1 = ans.first - 1;
  ll p2 = ans.second - 1;
  ll U = (1 << k) - 1;
  ll v1 = a[p1];
  ll v2 = a[p2];

  ll part1 = U - (v1 & v2);
  ll part2 = ((U - v1) & (U - v2));

  ll res = part1 | part2;

  ll answer = (res ^ v1) & (res ^ v2);

  cout << p1 + 1 << " " << p2 + 1 << " " << res << "\n";
}

void solve() {
  ll n, k; cin >> n >> k;
  vll a(n);
  vll b(n);
  ll U = (1 << k) - 1;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    b[i] = U - a[i];
  }

  ll res1 = 0;
  pll ans1 = {1, 2};
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      ll cur_res = a[i] & a[j];
      if (cur_res > res1) {
        ans1 = {i + 1, j + 1};
        res1 = cur_res;
      }
    }
  }

  
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