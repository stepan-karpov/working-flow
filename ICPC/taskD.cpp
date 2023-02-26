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

bool possible(vector<pair<ll, pll>>& a, ll need) {
  priority_queue<pll> q;

  ll p = 0;

  for (int cur_cell = 0; cur_cell <= 1'000'00; ++cur_cell) {
    while (p < a.size() && a[p].second.first <= cur_cell) {
      pll new_p = {0, -a[p].second.second};
      q.push(new_p);
      ++p;
    }
    while (!q.empty() && (-q.top().first >= need || -q.top().second < cur_cell)) {
      if (-q.top().first < need) {
        return false;
      }
      q.pop();
    }
    if (q.empty()) { continue; }
    pll temp = q.top();
    --temp.first;
    q.pop();
    q.push(temp);
  }

  return true;
}

ll binarySearch(vector<pair<ll, pll>>& a) {
  ll l = -1;
  ll r = 1e6 + 1;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (possible(a, m)) {
      l = m;
    } else {
      r = m;
    }
  }

  return l;
}

void solve() {
  ll n; cin >> n;

  vector<pair<ll, pll>> a(n);

  for (int i = 0; i < n; ++i) {
    cin >> a[i].second.first;
    cin >> a[i].second.second;
  }


  sort(a.begin(), a.end());

  // ll t = binarySearch(a) * n;
  // cout << t << "\n";
  // cout << "\n\n\n";

  // cout << possible(a, 0) << "\n";
  // cout << possible(a, 1) << "\n";
  cout << possible(a, 2) << "\n";
  cout << possible(a, 3) << "\n";
  cout << possible(a, 4) << "\n";
  cout << possible(a, 5) << "\n";

  

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