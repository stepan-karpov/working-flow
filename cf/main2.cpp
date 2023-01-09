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

void solve() {
  ll n;
  cin >> n;

  vvll matrix(n, vll(n, -1));

  ll cnt = 1;

  int i = n - 1;
  while (i >= -2 * n - 10) {
    int j = 0;
    int cp_i = i;
    while (cp_i <= n - 1 && j <= n - 1) {
      if (cp_i >= 0 && cp_i < n && j <= n - 1 && j >= 0) {
        matrix[cp_i][j] = cnt;
        ++cnt;
      }
      ++cp_i;
      ++j;
    }
    i -= 2;
  }

  i = 1;
  while (i <= 2 * n + 10) {
    int j = n - 1;
    int cp_i = i;
    while (cp_i >= 0 && j >= 0) {
      if (cp_i >= 0 && cp_i < n && j <= n - 1 && j >= 0) {
        matrix[cp_i][j] = cnt;
        ++cnt;
      }
      --cp_i;
      --j;
    }
    i += 2;
  }
  

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << matrix[i][j] << ' ';
    }
    cout << '\n';
  }

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