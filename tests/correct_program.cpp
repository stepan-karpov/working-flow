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

bool possible(std::vector<int>& a, std::vector<int>& b) {
  for (int i = 1; i < a.size(); ++i) {
    if (!(a[i] > a[i - 1])) {
      return false;
    }
  }
  if (a.size() == 0) {
    return true;
  }
  int p = 0;
  for (int i = 0; i < b.size(); ++i) {
    if (b[i] == a[p]) {
      ++p;
    }
    if (p == a.size()) {
      return true;
    }
  }
  return false;
}



void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  set<vector<ll>> ans;

  for (int i = 0; i < (1 << n); ++i) {
    vll temp2;
    for (int j = n - 1; j >= 0; --j) {
      bool t = (i >> j) & 1;
      if (t) {
        temp2.push_back(a[j]);
      }
    }
    vll temp;
    for (int j = temp2.size() - 1; j >= 0; --j) {
      temp.push_back(temp2[j]);
    }
    if (temp.size() != 0) {
      ans.insert(temp);
    }
  }

  std::cout << ans.size() << "\n";

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