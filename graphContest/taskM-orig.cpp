#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

typedef long long ll;
typedef std::pair<ll, ll> pll;
const ll INF = 1e9;

struct Edge {
  ll from, to, fl, c, paired;
  Edge* other; 
};

ll n, m;
std::vector<std::vector<Edge>> E;
std::vector<std::vector<Edge*>> ng;
std::vector<ll> used;
ll start, end;


bool bfs() {
  for (ll i = 0; i < 2 * n * m; ++i) {
    ng[i].clear();
  }
  std::vector<ll> d(2 * n * m, INF);
  d[start] = 0;
  std::queue<ll> q;
  q.push(start);
  while (!q.empty()) {
    ll v = q.front();
    q.pop();
    for (Edge e : E[v]) {
      if (e.fl < e.c && d[e.to] == INF) {
        d[e.to] = d[e.from] + 1;
        q.push(e.to);
      }
    }
  }
  for (ll i = 0; i < 2 * n * m; ++i) {
    for (Edge& e : E[i]) {
      if (d[e.from] + 1 == d[e.to] && e.fl < e.c) {
        ng[i].push_back(&e);
      }
    }
  }
  return d[end] != INF;
}


ll dfs(ll v, ll mn) {
  // std::cerr << "$: " << v << ' ' << mn << '\n';
  used[v] = 1;
  if (v == end) return mn;
  for (ll i = 0; i < ng[v].size(); ++i) {
    Edge* e = ng[v][i];
    if (e == nullptr) continue;
    // std::cerr << "#: " << v << ' ' << i << ' ' << e->to << '\n';
    if (e->fl < e->c && !used[e->to]) {
      ll mn2 = dfs(e->to, std::min(mn, e->c - e->fl));
      if (mn2 == 0) {
        ng[v][i] = nullptr;
      }
      if (mn2 > 0) {
        e->fl += mn2;
        (e->other)->fl -= mn2;
        return mn2;
      }
    }
  }
  return 0;
}

void dfs2(ll v) {
  used[v] = 1;
  if (v == end) return;
  for (Edge e : E[v]) {
    if (!used[e.to] && e.fl < e.c) {
      dfs2(e.to);
    }
  }
}

ll getNum1(ll x, ll y) {
  return x * n + y;
}

ll getNum2(ll x, ll y) {
  return n * m + getNum1(x, y);
}

bool onBoard(ll x, ll y) {
  return (0 <= x) && (x < m) && (0 <= y) && (y < n);
}

void add(ll x1, ll y1, ll x2, ll y2) {
  ll num1 = getNum2(x1, y1);
  ll num2 = getNum1(x2, y2);
  Edge e1, e2;
  e1.from = e2.to = num1;
  e1.to = e2.from = num2;
  e1.fl = e2.fl = 0;
  e1.c = INF;
  e2.c = 0;
  e1.paired = E[num2].size();
  e2.paired = E[num1].size();
  E[num1].push_back(e1);
  E[num2].push_back(e2);
}

signed main() {
  Init();
  std::cin >> m >> n;
  std::vector<std::vector<ll>> v(m, std::vector<ll>(n));
  ll k, l;
  std::cin >> k >> l;
  for (ll i = 0; i < k; ++i) {
    ll x, y;
    std::cin >> x >> y;
    v[x - 1][y - 1] = 1;
  }
  for (ll i = 0; i < l; ++i) {
    ll x, y;
    std::cin >> x >> y;
    v[x - 1][y - 1] = 2;
  }
  ll x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  start = getNum1(x1 - 1, y1 - 1);
  end = getNum2(x2 - 1, y2 - 1);
  E.resize(2 * n * m);
  ng.resize(2 * n * m);
  for (ll i = 0; i < m; ++i) {
    for (ll j = 0; j < n; ++j) {
      ll num1 = getNum1(i, j);
      ll num2 = getNum2(i, j);
      Edge e1, e2;
      e1.from = e2.to = num1;
      e1.to = e2.from = num2;
      e1.fl = e2.fl = 0;
      e2.c = 0;
      e1.paired = E[num2].size();
      e2.paired = E[num1].size();
      if (v[i][j] == 1) {
        e1.c = 0;
      } else if (v[i][j] == 2) {
        e1.c = 1;
      } else {
        e1.c = INF;
      }
      E[num1].push_back(e1);
      E[num2].push_back(e2);
      if (onBoard(i + 1, j)) {
        add(i, j, i + 1, j);
      }
      if (onBoard(i - 1, j)) {
        add(i, j, i - 1, j);
      }
      if (onBoard(i, j + 1)) {
        add(i, j, i, j + 1);
      }
      if (onBoard(i, j - 1)) {
        add(i, j, i, j - 1);
      }
    }
  }
  for (ll i = 0; i < 2 * n * m; ++i) {
    for (Edge &e : E[i]) {
      e.other = &E[e.to][e.paired];
    }
  }
  ll flow = 0;
  used.resize(2 * n * m);
  while(bfs()) {
    used.assign(2 * n * m, 0);
    while(ll add = dfs(start, INF)) {
      flow += add;
      used.assign(2 * n * m, 0);
    }
    if (flow >= INF) {
      std::cout << -1 << '\n';
      return 0;
    }
  }
  used.assign(2 * n * m, 0);
  dfs2(start);
  std::vector<pll> ans;
  for (ll i = 0; i < 2 * n * m; ++i) {
    for (Edge e : E[i]) {
      if (e.fl == e.c && e.c > 0 && used[i] && !used[e.to]) {
        ans.push_back(pll(e.from / n, e.from % n));
      }
    }
  }
  std::cout << ans.size() << '\n';
  for (auto& [x, y] : ans) {
    std::cout << x + 1 << ' ' << y + 1 << '\n';
  }
  return 0;
}