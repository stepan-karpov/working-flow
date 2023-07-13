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

bool FindIn(vll& temp, ll x) {
  for (int i = 0; i < temp.size(); ++i) {
    if (temp[i] == x) { return true; }
  }
  return false;
}

ll ans = -INF;
vll t;

void backtrack(vll temp) {
  if (temp.size() == 1) {
    ans = max(ans, temp[0]);
    return;
  }
  for (int i = 0; i < temp.size(); ++i) {
    vll copy1 = temp;
    if (i == 0 || i == temp.size() - 1) {
      copy1[i] = -INF;
    } else {
      copy1[i] = -INF;
      copy1[i - 1] += copy1[i + 1];
      copy1[i + 1] = -INF;
    }
    vll copy2;
    for (int j = 0; j < copy1.size(); ++j) {
      if (copy1[j] != -INF) {
        copy2.push_back(copy1[j]);
      }
    }
    backtrack(copy2);
  }
}

void solve() {
  ll n; cin >> n;
  t.assign(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> t[i];
  }

  backtrack(t);

  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  // cin >> t;
  // cout << fixed << setprecision(10);
  
  // freopen("a.out", "w", stdout);

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