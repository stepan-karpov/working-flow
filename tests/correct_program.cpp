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

int n;

vector<int> min(vector<int> &a, vector<int>& b) {
  for (int i = 0; i < n; ++i) {
    if (a[i] < b[i]) {
      return a;
    } else if (a[i] > b[i]) {
      return b;
    }
  }
  return a;
}

void solve() {
  cin >> n;
  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[i] = i + 1;
  }
  vector<vector<int>> v(n);
  for (int i = 0; i < n; ++i) {
    v[i].resize(i + 1);
    for (int& j : v[i]) cin >> j;
  }
  vector<int> ans(n, INF);
  do {
    int last = 0;
    vector<int> cur(n);
    for (int i = 0; i < n; ++i) {
      int ind = pos[i] - 1;
      for (int j = last; j < v[ind].size(); ++j) {
        cur[j] = v[ind][j];
        last++;
      }
    }
    ans = min(ans, cur);
  } while(next_permutation(pos.begin(), pos.end()));
  for (int i : ans) {
    cout << i << ' ';
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