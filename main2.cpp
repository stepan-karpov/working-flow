#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native") // Enable AVX/AVX2
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("rename-registers") // Optimization flags

#define ll int
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef long double ld;
const ll INF = 1e8;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

ll n, m, s, t;
vll p;
vll q;
set<ll> holes;
vll shortest_path;
vvll E;
vector<bool> used;
// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll FindBFS(ll start) {
  used.assign(E.size() + 1, 0);
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

bool possible(ll x, bool to_out = false) {
  set<ll> cool_values;
  unordered_map<int, vector<int>> mama;
  for (auto& ist : p) {
    mama[ist].assign(n, INF);
  }
  for (auto& ist : p) {
    for (auto& ist1 : p) {
      mama[ist][ist1] = 0;
    }
  }
  vector<int> papa;
  for (int i = 0; i < s; ++i) {
    if (shortest_path[i] <= x) { continue; }
    papa.emplace_back(p[i]);
    used.assign( n +1, false);
    queue<pair<int, int>> q;

    q.push({p[i], 0});

    while (!q.empty()) {

      ll cur_v = q.front().first;
      ll cur_d = q.front().second;
      q.pop();

      used[cur_v] = true;
      mama[p[i]][cur_v] = cur_d;

      if (cur_d >= x) { continue; }

      for (int j = 0; j < E[cur_v].size(); ++j) {
        ll to = E[cur_v][j];
        if (!used[to]) {
          q.push({to, cur_d + 1});
        }
      }
    }
  }
  set<ll> c;
  int ans = -1;
  for (int i = 0; i < n; ++i) {
    bool bad = false;
    for (auto& j : papa) {
      if (mama[j][i] > x) {
        bad = true;
      }
    }
    if (!bad) {
      ans = i;
      break;
    }
  }
    
  if (to_out) {
    std::cout << ans + 1 << ' ';
  }
  return true;

}

ll BinarySearch(ll max_ans) {
  ll l = -1;
  ll r = max_ans + 1;

  while (r - l > 1) {
    ll mid = (l + r) / 2;
    if (possible(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return r;
}

void solve() {
  cin >> n >> m >> s >> t;
  p.assign(s, 0);
  q.assign(t, 0);
  shortest_path.assign(s, 0);
  E.assign(n, {});
  for (int i = 0; i < s; ++i) {
    cin >> p[i];
    --p[i];
  }
  for (int i = 0; i < t; ++i) {
    cin >> q[i];
    --q[i];
    holes.insert(q[i]);
  }
  for (int i = 0; i < m; ++i) {
    ll u, v; cin >> u >> v;
    --u; --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  ll max_ans = -INF;
  for (int i = 0; i < s; ++i) {
    shortest_path[i] = FindBFS(p[i]);
    max_ans = max(max_ans, shortest_path[i]);
  }

  ll ans = BinarySearch(max_ans);
  possible(ans, true);
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