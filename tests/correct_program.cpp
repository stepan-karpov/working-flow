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

bool possible(int e_i, int e_j, int r, vvll& table) {
  int s_i = e_i - r + 1;
  int s_j = e_j - r + 1;
  if (s_i < 0 || s_i >= table.size()) {
    return false;
  }
  if (s_j < 0 || s_j >= table[0].size()) {
    return false;
  }

  for (int i = s_i; i <= e_i; ++i) {
    for (int j = s_j; j <= e_j; ++j) {
      if (table[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

void solve() {
  ll n, m; cin >> n >> m;
  vvll table(n, vll(m, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> table[i][j];
    }
  }

  ll ans = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ll r = 1;
      while (possible(i, j, r, table)) {
        ans = std::max(ans, r);
        ++r;
      }
    }
  }

  cout << ans << "\n";
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