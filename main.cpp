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

const ll INF = 1e18 * 2;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

struct Edge {
  ll u, c;
  Edge(ll u, ll c) : u(u), c(c) {}
};

struct printer {
  ll prepare, work;
  printer(ll prepare, ll work)
      : prepare(prepare), work(work) {}
};

bool possible(vector<printer>& pr, ll k, ll v, ll time) {
  vll printed;
  ll n = pr.size();

  for (int i = 0; i < n; ++i) {
    if (time <= pr[i].prepare) {
      continue;
    }
    ll delta = time - pr[i].prepare;
    printed.push_back(delta / pr[i].work);
  }

  sort(printed.begin(), printed.end());

  int taken = 0;
  ll sum = 0;
  for (int i = printed.size() - 1; i >= 0; --i) {
    if (taken > k) {
      break;
    }
    ++taken;
    sum += printed[i];
  }

  return (sum >= v);

}

void solve() {
  ll n, m, k;
  cin >> n >> m >> k;

  vector<vector<Edge>> E(n);

  for (int i = 0; i < m; ++i) {
    ll u, v; cin >> u >> v;
    --u; --v;
    ll c; cin >> c;
    E[u].push_back({v, c});
    E[v].push_back({u, c});
  }

  vll d(n, INF);
 
  d[0] = 0;
 
  set<pll> q;
  q.insert({d[0], 0});
 
  while (!q.empty()) {
    ll cur_vertex = q.begin()->second;
    q.erase(q.begin());
 
    for (int i = 0; i < E[cur_vertex].size(); ++i) {
      ll next_vertex = E[cur_vertex][i].u;
      ll new_dist = d[cur_vertex] + E[cur_vertex][i].c;
      if (new_dist < d[next_vertex]) {
        q.erase({d[next_vertex], next_vertex});
        d[next_vertex] = new_dist;
        q.insert({d[next_vertex], next_vertex});
      }
    }
  }

  ll s; cin >> s;

  vector<printer> pr;

  for (int i = 0; i < s; ++i) {
    ll v, hot, print;
    cin >> v >> hot >> print;
    --v;
    if (d[v] == INF) {
      continue;
    }
    pr.push_back({hot + d[v], print});
  }

  ll v; cin >> v;

  n = pr.size();

  ll l = -1;
  ll r = INF;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (possible(pr, k, v, m)) {
      r = m;
    } else {
      l = m;
    }
  }

  std::cout << r << "\n";

  // for (int i = 0; i < n; ++i) {
  //   std::cout << pr[i].prepare << " " << pr[i].work << "\n";
  // }


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