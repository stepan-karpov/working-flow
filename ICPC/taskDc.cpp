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

void Solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> v(n);
  for (auto& [a, b] : v) {
    cin >> a >> b;
    b++;
  }
  sort(v.begin(), v.end());
  int l = 0, r = 6;
  while(r - l > 1) {
    int mid = (r + l) / 2;
    int cur = -1;
    int bad = 0;
    for (auto [a, b] : v) {
      if (cur < a) cur = a;
      cur += mid;
      if (cur > b) {
        bad = 1;
        break;
      }
      // cout << mid << ' ' << cur << '\n';
    }
    if (bad) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << l * n << '\n';
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