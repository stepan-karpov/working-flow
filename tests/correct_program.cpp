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

bool tak = false;

void check(vll cur, ll n, vector<pll>& a, ll h) {
  if (cur.size() == a.size()) {
    for (int i = 0; i < cur.size(); ++i) {
      h -= a[cur[i]].first;
      if (h <= 0) {
        return;
      }
      h += a[cur[i]].second;
    }
    tak = true;
  } else {
    set<ll> nu;
    for (int i = 0; i < a.size(); ++i) {
      nu.insert(i);
    }
    for (int i = 0; i < cur.size(); ++i) {
      nu.erase(cur[i]);
    }
    for (auto el : nu) {
      cur.push_back(el);
      check(cur, n, a, h);
      cur.pop_back();
    }
  }
}

void solve() {
  ll n, h; cin >> n >> h;
  vector<pll> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }

  check({}, n, a, h);
  if (tak) {
    cout << "TAK\n";
  } else {
    cout << "NIE\n";
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