#include <bits/stdc++.h>
#include <regex>
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

bool f = false;

void backtrack(string& a, string& b, string cur) {
  if (a.size() == cur.size()) {
    string new_reg;
    for (int i = 0; i < cur.size(); ++i) {
      if (cur[i] == '*') {
        if (new_reg.empty() || new_reg[new_reg.size() - 1] != '*') {
          new_reg += "(.)*";
        }
      } else {
        new_reg += cur[i];
      }
    }
    int cnt_star = 0;
    int cnt_not_star = 0;
    for (int i = 0; i < new_reg.size(); ++i) {
      if (new_reg[i] == '*') {
        ++cnt_star;
      } else if (new_reg[i] != '(' && new_reg[i] != ')' && new_reg[i] != '.') {
        ++cnt_not_star;
      }
    }
    if (cnt_star > cnt_not_star) {
      return;
    }
    regex pat{ new_reg };
    bool match1 = regex_match(a, pat);
    bool match2 = regex_match(b, pat);
    if (match1 && match2) {
      f = true;
      // std::cout << new_reg << "\n";
    }
  } else {
    backtrack(a, b, cur + '*');
    backtrack(a, b, cur + a[cur.size()]);
  }
}

void solve() {
  string a, b;
  cin >> a >> b;
  if (a.size() < b.size()) {
    swap(a, b);
  }

  backtrack(a, b, "");
  backtrack(b, a, "");


  if (f) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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