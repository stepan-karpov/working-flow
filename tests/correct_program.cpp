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

ll Cnt(string& s, string search) {
  ll ans = 0;
  for (int i = 0; i < s.size(); ++i) {
    int start = i;
    int end = i + search.size() - 1;
    if (end >= s.size()) { break; }
    string cur_s = s.substr(start, search.size());
    if (cur_s == search) {
      ++ans;
    }
  }
  return ans;
}

void solve() {
  ll n, m; cin >> n >> m;
  string s; 
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    x -= 1;
    s += to_string(x);
  }

  string ans_s = "";
  ll ans = 0;

  for (int l = 0; l < s.size(); ++l) {
    for (int r = l; r < s.size(); ++r) {
      string sbstr = s.substr(l, r - l + 1);
      ll cur_ans = Cnt(s, sbstr) * sbstr.size();
      if (cur_ans > ans) {
        ans_s = sbstr;
        ans = cur_ans;
      }
    }
  }

  std::cout << ans << "\n";
  // std::cout << ans_s.size() << "\n";
  // for (int i = 0; i < ans_s.size(); ++i) {
  //   std::cout << ans_s[i] - '0' + 1 << " ";
  // }
  // std::cout << "\n";
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