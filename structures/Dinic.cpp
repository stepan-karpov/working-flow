#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vb = vector<bool>;

const ll INF = 1e16;

void BfsMarkup(ll s, vll& depth, vvll& matrix) {
  ll n = depth.size();
  queue<ll> q;
  q.push(s);
  depth[s] = 0;

  while (!q.empty()) {
    ll cur_v = q.front(); q.pop();

    for (int to = 0; to < n; ++to) {
      if (matrix[cur_v][to] == 0) { continue; }
      if (depth[to] == -1) {
        depth[to] = depth[cur_v] + 1;
        q.push(to);
      }
    }
  }
}

ll dfs(ll cur_v, ll cur_min, vb& used, vll& depth, vvll& matrix, vvll& weights) {
  ll n = matrix.size();
  if (cur_v == n - 1) { return cur_min; }
  if (used[cur_v]) { return 0; }
  used[cur_v] = true;

  for (int to = 0; to < n; ++to) {
    if (matrix[cur_v][to] == 0 || depth[to] - depth[cur_v] != 1) { continue; }
    ll cost = weights[cur_v][to];
    ll flow = matrix[to][cur_v];
    if (cost - flow > 0) {
      ll res = dfs(to, min(cost - flow, cur_min), used, depth, matrix, weights);
      if (res != 0) {
        matrix[cur_v][to] -= res;
        matrix[to][cur_v] += res;
        return res;
      }
    }
  }

  return 0;
}

ll BlockFlow(ll s, vll& depth, vvll& matrix, vvll& weights) {
  ll ans = 0;

  ll n = matrix.size();

  vb used(n, false);
  ll res = dfs(s, INF, used, depth, matrix, weights);

  while (res != 0) {
    ans += res;
    used.assign(n, false);
    res = dfs(s, INF, used, depth, matrix, weights);
  }
  return ans;
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
    matrix[u][v] += w;
    weights[u][v] += w;
    weights[v][u] += w;
  }
  
  ll ans = 0;

  vll depth(n, -1);
  BfsMarkup(0, depth, matrix);
  ll res = BlockFlow(0, depth, matrix, weights);

  while (res != 0) {
    ans += res;
    depth.assign(n, -1);
    BfsMarkup(0, depth, matrix);
    res = BlockFlow(0, depth, matrix, weights);
  }

  cout << ans << "\n";

  return 0;
}