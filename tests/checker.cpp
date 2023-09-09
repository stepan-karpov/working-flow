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

void output_test() {
  freopen("test.txt", "r", stdin);
  ll n; cin >> n;
  cout << n << " ";
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    cout << s << " ";
  }
}

void Solve() {
  // ll n; cin >> n;
  // vector<string> a(n);

  // for (int i = 0; i < n; ++i) {
  //   cin >> a[i];
  // }

  freopen("incorrect_answer.txt", "r", stdin);

  ll k;
  vll a;
  while (cin >> k) {
    a.push_back(k);
  }

  freopen("log.txt", "a", stdout);
  for (int i = 0; i < a.size() - 1; ++i) {
    if (a[i + 1] > a[i]) {
      output_test();
      return;
    }
  }

  // for (int i = 0; i < n; ++i) {
  //   sort(a[i].begin(), a[i].end());
  //   if (a[i] != "inw") {
  //     output_test();
  //     return;
  //   }
  // }

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