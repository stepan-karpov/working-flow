#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vb = vector<bool>;

const ll INF = 1e16;

ll bfs(ll source, vvll& matrix, vvll& weights) {
  ll n = matrix.size();

  vll parents(n, -1);

  ll best_cost = 0;

  queue<pll> q;
  q.push({source, INF});

  while (!q.empty()) {
    ll cur_v = q.front().first;
    ll cur_min = q.front().second;
    q.pop();

    if (cur_v == n - 1) {
      best_cost = cur_min;
      break;
    }

    for (int to = 0; to < n; ++to) {
      if (matrix[cur_v][to] == 0) { continue; }
      ll cost = weights[cur_v][to];
      ll flow = matrix[to][cur_v];
      if (cost - flow > 0 && parents[to] == -1) {
        parents[to] = cur_v;
        q.push({to, min(cost - flow, cur_min)});
      }
    }
  }
  if (best_cost == 0) { return best_cost; }

  ll cur_v = n - 1;
  while (cur_v != 0) {
    ll parent = parents[cur_v];
    if (parent == -1) { break; }
    matrix[parent][cur_v] -= best_cost;
    matrix[cur_v][parent] += best_cost;
    cur_v = parent;
  }

  return best_cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  ll n, m; cin >> n >> m;

  vvll matrix(n, vll(n, 0));
  vvll weights(n, vll(n, 0));

  for (int i = 0; i < m; ++i) {
    ll u, v, w; cin >> u >> v >> w;
    --u; --v;
    weights[u][v] += w;
    weights[v][u] += w;
    matrix[u][v] += w;
  }

  ll ans = 0;
  ll res = bfs(0, matrix, weights);

  while (res != 0) {
    ans += res;
    res = bfs(0, matrix, weights);
  }

  cout << ans << "\n";

  return 0;
}