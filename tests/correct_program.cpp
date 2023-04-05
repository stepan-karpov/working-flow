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

#define ll int
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef long double ld;
const ll INF = 1e8;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll FindBFS(ll start, vll& p, vvll& E, set<ll>& holes) {
  vll used(E.size() + 1);

  queue<pll> q;
  q.push({start, 0});

  while (!q.empty()) {
    ll cur_v = q.front().first;
    ll dist = q.front().second;
    q.pop();

    used[cur_v] = true;

    for (int i = 0; i < E[cur_v].size(); ++i) {
      ll to = E[cur_v][i];
      if (!used[to]) {
        if (holes.find(to) != holes.end()) {
          return dist + 1;
        }
        q.push({to, dist + 1});
      }
    }

  }
  return -1;
}

bool possible(ll x, ll n, ll m, ll s, ll t, vll& p, vll& q, set<ll>& holes, vll& shortest_path, vvll& E, bool to_out = false) {
  set<ll> cool_values;
  for (int i = 0; i < n; ++i) {
    cool_values.insert(i);
  }

  for (int i = 0; i < s; ++i) {
    if (shortest_path[i] <= x) { continue; }
    set<ll> new_cool_values;

    vector<bool> used(n + 1);
    queue<pair<int, int>> q;

    q.push({p[i], 0});

    while (!q.empty()) {

      ll cur_v = q.front().first;
      ll cur_d = q.front().second;
      q.pop();

      used[cur_v] = true;
      new_cool_values.insert(cur_v);

      if (cur_d >= x) { continue; }

      for (int j = 0; j < E[cur_v].size(); ++j) {
        ll to = E[cur_v][j];
        if (!used[to]) {
          q.push({to, cur_d + 1});
        }
      }
    }

    set<ll> c;

    if (cool_values.size() < new_cool_values.size()) {
      for (auto el : cool_values) {
        if (new_cool_values.find(el) != new_cool_values.end()) {
          c.insert(el);
        }
      }
    } else {
      for (auto el : new_cool_values) {
        if (cool_values.find(el) != cool_values.end()) {
          c.insert(el);
        }
      }
    }
    cool_values = c;
    if (cool_values.size() == 0) {
      return false;
    }
  }
  if (to_out) {
    std::cout << *cool_values.begin() + 1 << ' ';
  }
  return true;

}

ll BinarySearch(ll n, ll m, ll s, ll t, vll& p, vll& q, set<ll>& holes, vll& shortest_path, vvll& E, ll max_ans) {
  ll l = -1;
  ll r = max_ans + 1;

  while (r - l > 1) {
    ll mid = (l + r) / 2;
    if (possible(mid, n, m, s, t, p, q, holes, shortest_path, E)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return r;
}

void solve() {
  ll n, m, s, t;
  cin >> n >> m >> s >> t;
  vll p(s);
  vll q(t);
  set<ll> holes;
  vll shortest_path(s);
  for (int i = 0; i < s; ++i) {
    cin >> p[i];
    --p[i];
  }
  for (int i = 0; i < t; ++i) {
    cin >> q[i];
    --q[i];
    holes.insert(q[i]);
  }
  vvll E(n);
  for (int i = 0; i < m; ++i) {
    ll u, v; cin >> u >> v;
    --u; --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  ll max_ans = -INF;
  for (int i = 0; i < s; ++i) {
    shortest_path[i] = FindBFS(p[i], p, E, holes);
    max_ans = max(max_ans, shortest_path[i]);
  }

  ll ans = BinarySearch(n, m, s, t, p, q, holes, shortest_path, E, max_ans);
  possible(ans, n, m, s, t, p, q, holes, shortest_path, E, true);
  cout << ans << "\n";

  // cout << possible(0, n, m, s, t, p, q, holes, shortest_path, E) << "\n";
  // cout << possible(1, n, m, s, t, p, q, holes, shortest_path, E) << "\n";
  // cout << possible(2, n, m, s, t, p, q, holes, shortest_path, E) << "\n";
  // cout << possible(3, n, m, s, t, p, q, holes, shortest_path, E) << "\n";
  // cout << possible(4, n, m, s, t, p, q, holes, shortest_path, E) << "\n";
  // cout << possible(5, n, m, s, t, p, q, holes, shortest_path, E) << "\n";
  // cout << possible(6, n, m, s, t, p, q, holes, shortest_path, E) << "\n";
  // cout << possible(7, n, m, s, t, p, q, holes, shortest_path, E) << "\n";

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