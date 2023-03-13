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

ll cntAns(pll point, vector<pll>& organs) {
  ll ans = 0;
  for (int i = 0; i < organs.size(); ++i) {
    ll dx = organs[i].first - point.first;
    ll dy = organs[i].second - point.second;
    ans += dx * dx + dy * dy;
  }
  return ans;
}

void solve() {
  ll n, m;
  cin >> n >> m;
  vector<pll> organs(n);
  vector<pll> microbs(m);
  for (int i = 0; i < n; ++i) {
    cin >> organs[i].first;
    cin >> organs[i].second;
  }

  for (int i = 0; i < m; ++i) {
    cin >> microbs[i].first;
    cin >> microbs[i].second;
  }

  ll best_microb = 0;
  ll min_dist = cntAns(microbs[0], organs);

  for (int i = 1; i < m; ++i) {
    ll ans = cntAns(microbs[i], organs);
    if (ans < min_dist) {
      min_dist = ans;
      best_microb = i;
    } 
  }

  set<ll> not_added;
  for (int i = 0; i < m; ++i) {
    not_added.insert(i);
  }

  vll parent(m, -1);
  vll dist(m, INF);

  dist[best_microb] = 0;
  parent[best_microb] = -1;
  ll ans = 0;

  while (!not_added.empty()) {
    ll best = *not_added.begin();
    for (auto v : not_added) {
      if (dist[v] < dist[best]) {
        best = v;
      }
    }
    ans += dist[best];
    not_added.erase(best);

    for (auto x : not_added) {
      ll dx = microbs[x].first - microbs[best].first;
      ll dy = microbs[x].second - microbs[best].second;
      ll new_dist = dx * dx + dy * dy;
      if (new_dist < dist[x]) {
        parent[x] = best;
        dist[x] = new_dist;
      }
    }
  }
  cout << ans + min_dist << "\n";
  cout << m + n - 1 << "\n";

  for (int i = 0; i < m; ++i) {
    if (parent[i] != -1) {
      std::cout << "u " << parent[i] + 1 << " -> " << i + 1 << "\n"; 
    }
  }
  for (int i = 0; i < n; ++i) {
    std::cout << "s " << i + 1 << " -> " << best_microb + 1 << "\n";
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