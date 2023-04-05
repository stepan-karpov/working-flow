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
int cnt = 0;
void Bfs(ll start, vll& table, ll n, ll m, ll s, ll t, vll& p, vll& q, vvll& E) {
  queue<pll> qu;

  qu.push({start, 0});

  while (!qu.empty()) {
    cnt++;
    if (cnt == 30000) {
      break;
    }
    ll cur_v = qu.front().first;
    ll cur_d = qu.front().second;
    qu.pop();

    table[cur_v] = cur_d;
    
    for (int i = 0; i < E[cur_v].size(); ++i) {
      ll to = E[cur_v][i];
      if (table[to] == INF) {
        qu.push({to, cur_d + 1});
      }
    }
  }
}

void solve() {
  ll n, m, s, t; cin >> n >> m >> s >> t;
  vll p(s);
  vll q(t);
  for (int i = 0; i < s; ++i) {
    cin >> p[i];
    --p[i];
  }
  for (int i = 0; i < t; ++i) {
    cin >> q[i];
    --q[i];
  }
  vvll E(n);
  for (int i = 0; i < m; ++i) {
    ll u, v; cin >> u >> v;
    --u; --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  vvll table(s, vll(n, INF));

  for (int i = 0; i < s; ++i) {
    Bfs(p[i], table[i], n, m, s, t, p, q, E);
  }

  vll shortest_path(s, INF);

  for (int i = 0; i < s; ++i) {
    for (int j = 0; j < t; ++j) {
      shortest_path[i] = min(shortest_path[i], table[i][q[j]]);
    }
  }

  ll vert_ans = -1;
  ll col_ans = INF;

  for (int i = 0; i < n; ++i) {
    ll max_dist = -INF;
    for (int j = 0; j < s; ++j) {
      ll cur_dist = min(table[j][i], shortest_path[j]);
      max_dist = max(max_dist, cur_dist);
    }
    if (max_dist <= col_ans) {
      col_ans = max_dist;
      vert_ans = i;
    }
  }

  cout << vert_ans + 1 << " " << col_ans << "\n";

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