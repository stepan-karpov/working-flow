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

string createTemplate(string a, string b) {
  
  int p = 0;
  string ans;

  for (int i = 0; i < a.size(); ++i) {
    while (p < b.size() && b[p] != a[i]) {
      if (ans.empty() || ans[ans.size() - 1] != '*') {
        ans += '*';
      }
      ++p;
    }
    if (p >= b.size()) {
      if (ans.empty() || ans[ans.size() - 1] != '*') {
        ans += '*';
      }
      continue;
    } else {
      ans += b[p];
    }
    ++p;
  }

  return ans;
}

bool fits(string s) {
  int cnt_star = 0;
  int cnt_not_star = 0;


  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '*') {
      ++cnt_star;
    } else {
      ++cnt_not_star;
    }
  }

  if (cnt_star <= cnt_not_star) {
    return 1;
  }
  return 0;
}

void solve() {
  string a, b;
  cin >> a >> b;

  string t1 = createTemplate(a, b);
  if (fits(t1)) {
    cout << "YES\n";
    cout << t1 << '\n';
    return;
  }
  string t2 = createTemplate(a, b);
  if (fits(t2)) {
    cout << "YES\n";
    cout << t2 << '\n';
    return;
  }
  cout << "NO\n";
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