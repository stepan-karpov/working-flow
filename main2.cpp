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

ll FUNC(ll m, ll MV, ll n) {
  return max((m - MV + n - 1) / n + 1, 1ll);
}

ll solve() {
  ll n, k; cin >> n >> k;
  vll a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  if (a[0] != 1) {
    return 1;
  }

  set<ll> nums;
  ll DIGITS_NUM = 10000;
  vll func(DIGITS_NUM, INF);

  for (int i = 1; i <= DIGITS_NUM; ++i) {
    nums.insert(i);
  }

  for (ll day = 1; day <= 20; ++day) {
    vll to_delete;
    ll c = 1;
    ll p = 0;
    for (auto temp : nums) {
      if (c == a[p]) {
        ++p;
        to_delete.push_back(temp);
      }
      if (p == n) { break; }
      ++c;
    }
    for (int i = 0; i < to_delete.size(); ++i) {
      if (to_delete[i] < 10)
        cout << " ";
      cout << to_delete[i] << " ";
      nums.erase(to_delete[i]);
    }
    cout << "\n";
  }

  return -1;
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
    cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}