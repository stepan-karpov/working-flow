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

void solve() {
  ll testcase; cin >> testcase;
  for (int temp = 0; temp < testcase; ++temp) {
    string s1, s2; cin >> s1 >> s2;
    vll a(35, -1);
    vll b(35, -1);
    bool ok = true;
    for (int i = 0; i < s1.size(); ++i) {
      ll c1 = s1[i] - 'a';
      ll c2 = s2[i] - 'a';
      if (a[c1] == -1) {
        a[c1] = c2;
      } else {
        if (c2 != a[c1]) {
          ok = false;
        }
      }
      if (b[c2] == -1) {
        b[c2] = c1;
      } else {
        if (c1 != b[c2]) {
          ok = false;
        }
      }
    }
    if (ok) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
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