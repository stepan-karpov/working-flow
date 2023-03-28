#include <algorithm>
#include <iostream>
#include <vector>

struct Var {
  int coef = 0, b = 0;
  Var(int coef, int b) : coef(coef), b(b) {}
  Var() = default;
};

struct Edge {
  int from, to, val;
  Edge(int from, int to, int val) : from(from), to(to), val(val) {}
};

std::vector<std::vector<Edge>> g;
std::vector<int> used;
std::vector<Var> t;

void Dfs(int v) {
  used[v] = 1;
  for (Edge e : g[v]) {
    if (used[e.to] == 0) {
      t[e.to].coef = -t[v].coef;
      t[e.to].b = e.val - t[v].b;
      Dfs(e.to);
    }
  }
}

int n, m;

bool Fill(std::vector<int>& ans, int x) {
  std::vector<bool> was(n + 1, true);
  for (int i = 0; i < n; ++i) {
    if (ans[i] != 0) {
      return false;
    }
    int num = 1 + t[i].coef * x + t[i].b;
    if (num > n || num < 1) {
      return false;
    }
    if (!was[num]) {
      return false;
    }
    ans[i] = num;
    was[num] = false;
  }
  for (int i = 0; i < n; ++i) {
    std::cout << ans[i] << ' ';
  }
  return true;
}

signed main() {
  std::cin >> n >> m;
  g.resize(n);
  std::vector<Edge> all;
  for (int i = 0; i < m; ++i) {
    int v, u, cost;
    std::cin >> v >> u >> cost;
    v--;
    u--;
    cost -= 2;
    g[v].push_back(Edge(v, u, cost));
    g[u].push_back(Edge(u, v, cost));
    all.push_back(Edge(v, u, cost));
  }
  t.resize(n);
  used.resize(n);
  t[0] = Var(1, 0);
  Dfs(0);
  int x = 0;
  for (int i = 0; i < m; ++i) {
    int l = t[all[i].from].coef;
    int r = t[all[i].to].coef;
    if (l == r) {
      if (l == -1) {
        x = (t[all[i].from].b + t[all[i].to].b - all[i].val) / 2;
      } else {
        x = -(t[all[i].from].b + t[all[i].to].b - all[i].val) / 2;
      }
      std::vector<int> ans(n);
      Fill(ans, x);
      return 0;
    }
  }
  int mx = -1e9;
  for (int i = 0; i < n; ++i) {
    if (t[i].coef == 1) {
      mx = std::max(t[i].b, mx);
    }
  }
  x = n - 1 - mx;
  std::vector<int> ans(n);
  if (Fill(ans, x)) {
    return 0;
  }
  mx = -1e9;
  for (int i = 0; i < n; ++i) {
    if (t[i].coef == -1) {
      mx = std::max(t[i].b, mx);
    }
  }
  x = -(n - 1 - mx);
  ans.assign(n, 0);
  Fill(ans, x);
  return 0;
}