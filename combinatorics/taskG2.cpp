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

using ll = int;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;

const ld EPS = 1e-8;
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

void Solve() {
  ll n;
  cin >> n;
  vll lp(n + 1, 0);
  vll pr;
  lp[1] = 1;
  vll euler(n + 1, 1);
  long long sum = 0;
  for (ll i = 2; i <= n; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      euler[i] = i - 1;
      pr.push_back(i);
    }
    for (ll j = 0; j < pr.size() && i * pr[j] <= n; ++j) {
      lp[i * pr[j]] = pr[j];
      euler[i * pr[j]] =  (i % pr[j] == 0) ? pr[j] : (pr[j] - 1);
      euler[i * pr[j]] *= euler[i]; 
      if (pr[j] == lp[i]) {
        break;
      }
    }
    sum += euler[i];
  }
  vll f(n + 1, 0);
  f[1] = 1;
  for (ll i = 2; i <= n; ++i) {
    f[i] = f[i - 1] + 2 * euler[i];
  }
  long long ans = 0;
  for (ll i = 1; i <= n; ++i) {
    ans += i * f[n / i];
  }
  cout << ans << '\n';

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