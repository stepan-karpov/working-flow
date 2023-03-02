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

ll findChain(ll start, ll l, ll r, ll mult) {
  ll ans = 1;

  ll cur = start;

  while (true) {
    cur *= mult;
    if (cur <= r) {
      ++ans;
    } else {
      break;
    }
  }

  return ans;
}

ll findWithMult(ll L, ll R, ll mult, ll chain_size) {
  ll l = L - 1;
  ll r = R + 1;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    ll temp = findChain(m, L, R, mult);
    if (temp >= chain_size) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

ll getNumber(ll start, ll L, ll R, ll size) {
  ll end = start;
  for (int i = 0; i < size - 1; ++i) {
    end *= 2;
  }
  
  ll ans = 1;

  ll max_j = 2 * R / end;

  ans += (size - 1) * (max_j - 2);

  // for (int j = 3; j <= 1e6; ++j) {
  //   if (end / 2 * j > R) {
  //     break;
  //   }
  //   ans += size - 1;
  // }

  return ans;

}

void solve() {
  ll L, R; cin >> L >> R;

  ll res = findChain(L, L, R, 2);

  ll ans = 0;

  for (int start = L; start <= findWithMult(L, R, 2, res); ++start) {
    ll t = getNumber(start, L, R, res);
    ans += t;
  }

  cout << res << " " << ans << "\n";

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