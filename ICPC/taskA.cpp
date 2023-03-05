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

struct Edge {
  ll u, w, is_cap;
  Edge(ll u, ll w, ll is_cap) : w(w), is_cap(is_cap) {}
};

void solve() {
  ll n, m, k;
  cin >> n >> m >> k;

  vector<vector<Edge>> E(n);

  for (int i = 0; i < m; ++i) {
    ll u, v; cin >> u >> v;
    --u; --v;
    ll w, f; cin >> w >> f;
    E[u].push_back({v, w, f});
    E[v].push_back({u, w, f});
  }

  vector<pll> times(k);

  for (int i = 0; i < k; ++i) {
    ll t1, t2; cin >> t1 >> t2;
    times[i] = {t1, t2};
  }

  ll start, end, start_time;
  cin >> start >> end >> start_time;

  --start; --end;

  vll d(n, INF);
  d[start] = start_time;

  set<pll> q;
  q.insert({d[start], start});

  while (!q.empty()) {
    ll cur_vertex = q.begin()->second;
    q.erase(q.begin());

    for (int i = 0; i < E[cur_vertex].size(); ++i) {
      ll next_vertex = E[cur_vertex][i].u;
      ll new_dist = d[cur_vertex] + E[cur_vertex][i].w;
      if (new_dist < d[next_vertex]) {
        q.erase({d[next_vertex], next_vertex});
        d[next_vertex] = new_dist;
        q.insert({d[next_vertex], next_vertex});
      }
    }
  }

  std::cout << d[end] << "\n";




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