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

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef long double ld;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

void Solve() {
  ll n; cin >> n;
  vll a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vll cnt(200'100, 0);

  set<pll> prefixes;
  int ans = 0;

  for (int i = 0; i < n; ++i) {
    int last_cnt = cnt[a[i]];
    prefixes.erase({last_cnt, a[i]});
    prefixes.insert({last_cnt + 1, a[i]});
    ++cnt[a[i]];

    if (prefixes.size() == 1) {
      auto it1 = prefixes.begin();
      ans = max(ans, i + 1);
    } else if (prefixes.size() == 2) {
      auto it1 = prefixes.begin();
      auto it2 = prefixes.begin(); ++it2;
      if (it2->first - it1->first == 1) {
        ans = max(ans, i + 1);
      }
      if (it1->first == 1) {
        ans = max(ans, i + 1);
      }
    } else if (prefixes.size() == 3) {
      auto it1 = prefixes.begin();
      auto it2 = prefixes.begin(); ++it2;
      auto it3 = prefixes.begin(); ++it3; ++it3;

      if (it1->first == 1 && it2->first == 1 && it3->first == 1) {
        ans = max(ans, i + 1);
      }
      if (it1->first == 1 && it2->first == it3->first) {
        ans = max(ans, i + 1);
      }
      if (it3->first - it2->first == 1 && it1->first == it2->first) {
        ans = max(ans, i + 1);
      }

    } else if (prefixes.size() >= 4) {
      auto it1 = prefixes.begin();
      auto it2 = prefixes.begin(); ++it2;
      auto it3 = prefixes.end(); --it3; --it3;
      auto it4 = prefixes.end(); --it4;
      if (it1->first == 1 && it2->first == 1 && it3->first == 1 && it4->first == 1) {
        ans = max(ans, i + 1);
      }
      if (it4->first == it2->first && it1->first == 1) {
        ans = max(ans, i + 1);
      }
      if (it4->first - it3->first == 1 && it3->first == it1->first) {
        ans = max(ans, i + 1);
      }
    }
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