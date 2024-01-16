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
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vb = vector<bool>;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

int SQRT = 320;

struct Node {
  vll neighbors;
  ll count = 0;
  ll to_add = 0;
  vll heavy;
  Node() = default;
};

void solve() {
  ll n, m, q; cin >> n >> m >> q;
  vector<Node> graph(n);

  for (int i = 0; i < n; ++i) {
    cin >> graph[i].count;
  }
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v; --u; --v;
    graph[u].neighbors.push_back(v);
    graph[v].neighbors.push_back(u);
  }

  for (int i = 0; i < n; ++i) {
    for (auto to : graph[i].neighbors) {
      bool is_heavy = graph[to].neighbors.size() >= SQRT;
      if (is_heavy) {
        graph[i].heavy.push_back(to);
      }
    }
  }

  for (int i = 0; i < q; ++i) {
    string query; cin >> query;
    if (query == "?") {
      ll v; cin >> v; --v;
      ll answer = graph[v].count;
      for (auto to : graph[v].heavy) {
        answer += graph[to].to_add;
      }
      cout << answer << "\n";
    } else {
      ll v, x; cin >> v >> x; --v;
      if (graph[v].neighbors.size() >= SQRT) {
        graph[v].to_add += x;
      } else {
        for (auto to : graph[v].neighbors) {
          graph[to].count += x;
        }
      }
    }
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