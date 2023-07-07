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

ll BinPow(ll k, ll x) {
  if (x == 0) {
    return 1;
  }
  if (x % 2 == 0) {
    ll t = BinPow(k, x / 2);
    return t * t;
  } else {
    return k * BinPow(k, x - 1);
  }
}

bool solve() {
  ll n; cin >> n;

  for (int k = 2; k < 500; ++k) {
    ll cur_power = 0;
    ll cur = 0;

    while (cur < n) {
      cur += BinPow(k, cur_power);
      ++cur_power;
    }
    if (n == cur && cur_power != 2) {
      return true;
    }
  }

  for (int x = 3; x <= 10; ++x) {
    ll l = 2;
    ll r = pow(10, 18 / x);
    while (r - l > 1) {
      ll m = (l + r) / 2;
      ll value = (BinPow(m, x) - 1) / (m - 1);
      if (value > n) {
        r = m;
      } else {
        l = m;
      }
    }
    ll value1 = (BinPow(l, x) - 1) / (l - 1);
    ll value2 = (BinPow(l + 1, x) - 1) / (l);
    if (value1 == n || value2 == n) {
      return true;
    } 
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  // cin >> t;
  // cout << fixed << setprecision(10);
  
  while (t--) {
    // solve();
    // cout << solve() << endl;
    if (solve())
       cout << "YES" << endl;
    else
       cout << "NO" << endl;
  }

  return 0;
}