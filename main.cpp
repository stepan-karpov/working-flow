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
  string s1; cin >> s1;
  string s2; cin >> s2;

  ll n1 = s1.size();
  ll n2 = s2.size();

  vvll dp(n1 + 1, vll(n2 + 1, INF));

  for (int i = 0; i <= n1; ++i) {
    dp[i][0] = i;
  }
  for (int i = 0; i <= n2; ++i) {
    dp[0][i] = i;
  }


  for (int i = 1; i <= n1; ++i) {
    for (int j = 1; j <= n2; ++j) {
      if (s1[i - 1] == s2[j - 1] ) { // last are equal
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = min({dp[i][j], dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1});
      }
      if (i >= 2 && j >= 2) {
        if (s1[i - 2] == s2[j - 1] && s1[i - 1] == s2[j - 2]) {
          dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + 1);
        }
      }
    }
  }

  cout << dp[n1][n2] << "\n";
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