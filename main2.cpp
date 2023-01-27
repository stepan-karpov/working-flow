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
const ll MOD = 1e9 + 7;

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll BinPow(ll a, ll x) {
  if (x == 0) {
    return 1;
  }
  if (x == 1) {
    return a % MOD;
  }
  if (x % 2 == 0) {
    ll t = BinPow(a, x / 2);
    return (t * t) % MOD;
  } else {
    return (a * BinPow(a, x - 1)) % MOD;
  }
}

void solve() {
  ll n; cin >> n;

  vll C(n + 10);
  vll fact(n + 10);
  fact[0] = 1;
  for (ll i = 1; i <= n; ++i) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= MOD;
  }

  for (ll i = 1; i <= n; ++i) {
    ll temp = i;
    temp *= (i - 1);
    C[i] = temp / 2;
    C[i] %= MOD;
  }

  vll a(n + 10);
  a[0] = 0;
  a[1] = 1;

  for (int i = 2; i <= n; ++i) {
    ll ans = C[i - 1];
    for (int j = i - 1; j >= 0; --j) {
      ll curC =  fact[i - 1];
      curC *= BinPow(fact[i - 1 - j], MOD - 2);
      curC %= MOD;
      curC *= BinPow(fact[j], MOD - 2);
      curC %= MOD;
      ll temp = a[j] * curC;
      temp %= MOD;
      ans = ans + temp;
      ans %= MOD;
    }
    a[i] = i;
    ll temp = BinPow(2, C[i - 1]) - ans + MOD;
    temp %= MOD;
    a[i] *= temp;
    a[i] %= MOD;
  }

  cout << a[n] << '\n';
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