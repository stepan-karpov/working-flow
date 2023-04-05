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
#define int long long
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
using namespace std;
void solve() {
  ll n, m, s, t;
  cin >> n >> m >> s >> t;
  vll p(s);
  vll q(t);
  set<ll> holes;
  vll shortest_path(s, INF);
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

  for (int i = 0; i < s; ++i) {
    shortest_path[i] = FindBFS(p[i], p, E, holes);
  }
    cout << "\n\ntest\n\n";

  for (int i = 0; i < s; ++i) {
    std::cout << shortest_path[i] << " ";
  }
  cout << "\n\ntest\n\n";
  
  vector<pair<int, int>> ans_for;
  for (int i = 0; i < s; ++i) {
    ans_for.emplace_back(shortest_path[i], i);
  }
  sort(ans_for.begin(), ans_for.end());
  vector<int> current(n);
  auto get_ans = [&](int cur_rast) -> int {
    vector<int> gogo;
    vector<vector<int>> cost(s, vector<int>(n));
    int cnt = 0;
    for (auto& kap : p) {
      vll used(n);
      queue<pll> q;
      q.push({kap, 0});
      bool bad_boy = false;


      while (!q.empty() && !bad_boy) {
        ll cur_v = q.front().first;
        ll dist = q.front().second;
        q.pop();
        if (cur_v == 0) {
          cout << "\n\n\n\n\nWOWOWOWOWO\n\n\n\n";
          cout << cost[cnt][cur_v] << " ";
          cout << "\n\n\n\n\nWOWOWOWOWO\n\n\n\n";
        }
        
        cost[cnt][cur_v] = dist;
        used[cur_v] = true;
        
        for (int i = 0; i < E[cur_v].size(); ++i) {
          ll to = E[cur_v][i];
          if (!used[to]) {
            if (holes.find(to) != holes.end()) {
              bad_boy = true;
              break;
            }
            if (dist + 1 <= cur_rast) {
              q.push({to, dist + 1});
            }
          }
        }

      }

      if (!bad_boy) {
        gogo.emplace_back(cnt);
      }
      cnt++;
    }

    int finded = -1;
    for (int vert = 0; vert < n; ++vert) {
      bool curcur = true;
      for (auto& kap : gogo) {
        if (cost[kap][vert] > cur_rast) {
          curcur = false;
        }
      }
      if (curcur) {
        finded = vert;
        break;
      }
    }
    return finded;
    
  };
  int l = 0, r = n;
  //cout << "lol";
  pair<int, int> ans;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (get_ans(mid) != -1) {
      ans = {get_ans(mid), mid};
      cout << "CURRENT\n\n";
      cout << get_ans(mid) << " " << mid << "\n\n";
      r = mid;
    } else {
      l = mid;
    }
    
  }
  cout << "\n\ntest\n\n" <<  ans_for.back().second + 1 << " " << ans_for.back().first  << "\n\ntest\n\n";
  if (ans.first == -1) {
    cout << ans_for.back().second + 1 << " " << ans_for.back().first ;
    return;
  }
  cout << ans.first + 1 << " " << ans.second;
}

signed main() {
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