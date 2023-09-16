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

void Shift(string& s) {
  char start = s.front();
  char end = s.back();

  string ans = end + s.substr(0, s.size() - 1);
  s = ans;
}

ll CountEntries(string s, string t) {
  ll ans = 0;

  for (int i = 0; i < t.size(); ++i) {
    bool ok = true;

    for (int j = 0; j < s.size(); ++j) {
      if (i + j >= t.size() || s[j] != t[i + j]) {
        ok = false;
      }
    }
    ans += ok;
  }
  return ans;
}

void Solve() {
  string s; cin >> s;
  string t; cin >> t;
  
  ll ans = 0;

  set<string> options;

  for (int i = 0; i < s.size(); ++i) {
    if (options.find(s) == options.end()) {
      ans += CountEntries(s, t);
    }
    options.insert(s);
    Shift(s);
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