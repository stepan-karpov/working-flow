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
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

bool is_substr(string t, int start, string s) {
  for (int i = 0; i < s.size(); ++i) {
    if (i + start >= t.size()) { return false; }
    if (t[i + start] != s[i]) { return false; }
  }
  return true;
}

bool prefix_eq(string& text, string& pattern, int r) {
  int start = text.size() - r;
  for (int i = 0; i < r; ++i) {
    if (start + i < 0 || start + i >= text.size()) { return false; }
    if (text[start + i] != pattern[i]) { return false; }
  }
  return true;
}

void Solve() {
  ll n; cin >> n;
  std::vector<string> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  string ans = a[0];

  for (int i = 1; i < n; ++i) {
    int max_delete = 0;
    for (int j = 1; j <= a[i].size(); ++j) {
      if (prefix_eq(ans, a[i], j)) {
        max_delete = j;
      }
    }
    ans += a[i].substr(max_delete, a[i].size() - max_delete);
  }
  std::cout << ans << "\n";
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