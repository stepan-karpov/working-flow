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

ll BinarySearch1() {
  ll l = 0;
  ll r = 18;
  int last_step = 0;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    ll q = m - last_step;
    last_step = m;
    cout << "? " << -q << endl;
    string s1, s2; cin >> s1 >> s2;
    if (s2 == "side") {
      l = m;
    } else {
      r = m;
    }
  }
  cout << "! " << 37 + l << endl;
  return 0;
}

ll BinarySearch2() {
  ll l = 0;
  ll r = 36;
  int last_step = 0;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    ll q = m - last_step;
    last_step = m;
    cout << "? " << q << endl;
    string s1, s2; cin >> s1 >> s2;
    if (s2 == "main") {
      l = m;
    } else {
      r = m;
    }
    cerr << l << ' ' << r << endl;
  }
  cout << "! " << 1 + l << endl;
  return 0;
}


void solve() {
  std::cout << "? 0" << endl;
  string s1, s2; cin >> s1 >> s2;

  if (s2 == "side") {
    BinarySearch1();
  } else {
    BinarySearch2();
  }
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