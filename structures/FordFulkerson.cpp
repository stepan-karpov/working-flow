#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vb = vector<bool>;

const ll INF = 1e16;

ll dfs(ll cur_v, ll min_v, vvll& matrix, vvll& weights, vb& used) {
  ll n = matrix.size();
  if (cur_v == n - 1) { return min_v; }
  if (used[cur_v]) { return 0; }
  used[cur_v] = true;

  for (int to = 0; to < n; ++to) {
    if (matrix[cur_v][to] == 0) { continue; }
    ll capacity = weights[cur_v][to];
    ll flow = matrix[to][cur_v];
    if (capacity - flow > 0) {
      ll res = dfs(to, min(capacity - flow, min_v), matrix, weights, used);
      if (res != 0) {
        matrix[cur_v][to] -= res;
        matrix[to][cur_v] += res;
        return res;
      }
    }
  }
  return 0;
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
  vb used(n, false);

  ll ans = 0;
  ll res = dfs(0, INF, matrix, weights, used);

  while (res != 0) {
    ans += res;
    used.assign(n, false);
    res = dfs(0, INF, matrix, weights, used);
  }

  cout << ans << "\n";

  return 0;
}