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
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

void Solve() {
  ll m, n; cin >> n >> m;
  vll a(n);
  vll b(m);
  int MAX = 1e5 + 10;
  vector<set<ll>> jopa(MAX + 10);
  set<ll> used;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }

  sort(a.begin(), a.end());

  for (int i = 0; i < n; ++i) {
    for (int j = 1; a[i] * j <= MAX; ++j) {
      jopa[a[i] * j].insert(i);
      used.insert(a[i] * j);
    }
  }

  int free = 0;

  for (int i = 0; i < m; ++i) {
    if (free > 0) {
      --free;
      cout << b[i] << " ";
      continue;
    }
    int next_ass = *used.lower_bound(b[i]);
    set<ll> to_delete = jopa[next_ass];
    free += to_delete.size() - 1;
    for (ll el : to_delete) {
      int delete_value = a[el];
      for (int j = 1; j * delete_value <= MAX; ++j) {
        if (jopa[delete_value * j].size() == 1 && 
            jopa[delete_value * j].find(el) != jopa[delete_value * j].end()) {
          used.erase(a[el] * j);
        } 
        jopa[a[el] * j].erase(el);
      }
    }
    cout << next_ass << " ";
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
    Solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}