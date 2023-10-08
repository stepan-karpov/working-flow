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

set<ll> possible;

string Ans(ll sit) {
  if (1 <= sit && sit <= 36) {
    if (sit % 2 == 0) {
      return "highmain";
    }
    return "lowmain";
  }
  if (sit % 2 == 0) {
    return "highside";
  }
  return "lowside";
}

bool CanBe(int sit, std::vector<pair<string, int>>& q) {
  for (int i = 0; i < q.size(); ++i) {
    sit += q[i].second;
    if (Ans(sit) != q[i].first) { return false; }
  }
  return true;
}

void ClearVars(std::vector<pair<string, int>>& q) {
  set<ll> n_v;
  for (auto el : possible) {
    if (CanBe(el, q)) {
      n_v.insert(el);
    }
  }
  possible = n_v;
}

void solve() {
  for (int i = 1; i <= 54; ++i) {
    possible.insert(i);
  }
  std::vector<pair<string, int>> q;
  std::cout << "? 0" << endl;
  string s1, s2; cin >> s1 >> s2;
  q.push_back({s1 + s2, 0});

  ClearVars(q);

  ll current = 0;

  while (possible.size() > 1) {
    if (q[q.size() - 1].first == "highmain" || q[q.size() - 1].first == "lowmain") {
      ll add = INF;
      for (auto el : possible) {
        add = min(add, 54 - el - current);
      }
      std::cout << "? " << add << endl;
      string s1, s2; cin >> s1 >> s2;
      current += add;
      q.push_back({s1 + s2, add});
      ClearVars(q);
    } else {
      ll add = INF;
      for (auto el : possible) {
        add = min(add, el + current - 1);
      }
      add = -add;
      std::cout << "? " << add << endl;
      string s1, s2; cin >> s1 >> s2;
      current += add;
      q.push_back({s1 + s2, add});
      ClearVars(q);
    }
  }
  std::cout << "! " << *possible.begin() << "\n";
}

void solve2() {
  string ananas1;
  string ananas2;
  cout << "? 0\n";
  cin >> ananas1 >> ananas2;
  int cur = 0;
  if (ananas2 == "side") {
    int l = 0, r = 19;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      int len = -(mid + cur);
      cur += abs(len);
      cout << "? " << len << endl;
      cin >> ananas1 >> ananas2;
      if (ananas2 == "side") {
        l = mid;
      } else {
        r = mid;
      }
    }
    cout << "! " << 36 + l;
  } else {
    cout << "v razrabotke\n";
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
    solve2();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}