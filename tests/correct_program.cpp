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

ll ans = 1e18;

void backtrack(vll current, vll& a, vll& b) {
  if (current.size() == b.size()) {
    ll sum = 0;
    for (int i = 0; i < a.size(); ++i) {
      sum += abs(a[i] - b[current[i]]);
    }
    ans = min(ans, sum);
  }
  set<ll> not_used;
  for (int i = 0; i < b.size(); ++i) {
    not_used.insert(i);
  }
  for (int i = 0; i < current.size(); ++i) {
    not_used.erase(current[i]);
  }

  for (auto p : not_used) {
    current.push_back(p);
    backtrack(current, a, b);
    current.pop_back();
  }
}


void solve() {
  ll n; cin >> n;
  cout << n + 1 << "\n";
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