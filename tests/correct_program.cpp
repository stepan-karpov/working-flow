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

bool is_segment_equal(string& s, int ind, string pattern) {
  for (int i = 0; i < pattern.size(); ++i) {
    if (ind + i >= s.size()) { return false; }
    if (s[ind + i] != pattern[i]) { return false; }
  }
  return true;
}

void Solve() {
  string s; cin >> s;
  ll n = s.size();
  ll ans = 0;
  for (int l = 0; l < n; ++l) {
    for (int r = l; r < n; ++r) {
      ll current_score = 0;
      int ind = l;
      while (is_segment_equal(s, ind, s.substr(l, r - l + 1))) {
        ++current_score;
        ind += r - l + 1;
      }
      ans = max(ans, current_score);
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
    Solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}