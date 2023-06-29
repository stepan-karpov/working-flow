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

ll Count(ll min_v, vll& a) {
  bool achieved = false;
  ll rate = 0;

  for (int i = 0; i < a.size(); ++i) {
    if (rate >= min_v) {
      achieved = true;
    }
    if (achieved) {
      rate = max(min_v, rate + a[i]);
    } else {
      rate += a[i];
    }
  }
  return rate;
}

ll BinarySearchR(vll& a, ll max_achieved) {
  ll l = -1;
  ll r = max_achieved + 1;

  while (r - l > 2) {
    ll m1 = l + (r - l) / 3;
    ll m2 = r - (r - l) / 3;

    ll cnt1 = Count(m1, a);
    ll cnt2 = Count(m2, a);

    if (cnt1 > cnt2) {
      r = m2;
    } else {
      l = m1;
    }
  }


  ll max_v = Count(l, a);
  ll ans = l;

  for (int i = l - 10; i <= 10; ++i) {
    if (Count(l + i, a) > max_v) {
      max_v = Count(l + i, a);
      ans = l + i;
    }
  }

  return ans;
}

void solve() {
  ll n; cin >> n;
  vll a(n);
  ll max_achieved = 0;
  ll rate = 0;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    rate += a[i];
    max_achieved = max(max_achieved, rate);
  }

  // for (int i = 0; i <= max_achieved; ++i) {
  //   cout << i << ": " << Count(i, a) << "\n";
  // }

  cout << BinarySearchR(a, max_achieved) << "\n";
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