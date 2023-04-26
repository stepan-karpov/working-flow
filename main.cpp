#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("fast-math")
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC optimize "-O3"
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2") // Enable AVX/AVX2
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("rename-registers") // Optimization flags

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef long double ld;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

void solve() {
  ll a, b, m, x0, x;
  cin >> a >> b >> m >> x0 >> x;

  ll last = x0;


  ll max_value = m;

  if (max_value > 2'500'000'0) {
    max_value = 2'500'000'0;
  }

  set<ll> used;

  for (int i = 0; i < max_value; ++i) {
    if (x == last) {
      std::cout << "YES\n";
      return;
    }
    if (used.find(last) != used.end()) {
      std::cout << "NO\n";
      return;
    }
    last = (a * last + b) % m;
    used.insert(last);
  }

  std::cout << "NO\n";


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