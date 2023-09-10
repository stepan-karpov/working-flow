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
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

void Solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> v(n);
  for (pair<int, int>& p : v) {
    cin >> p.first >> p.second;
  }
  int mx = 0;
  int ans_a, ans_b;
  for (int i = 0; i < n; ++i) {
    int a = v[i].first, b = v[i].second;
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
      if ((v[j].first <= a && v[j].second <= b) || (v[j].first <= b && v[j].second <= a)) {
        cnt++;
      }
    }
    if (a * b * cnt > max) {
      max = a * b * cnt;
      ans_a = a;
      ans_b = b;
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
    Solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}