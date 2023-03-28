#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Node {
  int x, w;
  Node(int x, int w) : x(x), w(w) {}
};

struct Three {
  int u, v, w;
  Three(int u, int v, int w) : u(u), v(v), w(w) {}
};

void Dfs(int current_v, std::vector<bool>& used,
         std::vector<std::pair<int, int>>& equation,
         std::vector<std::vector<Node>>& g) {
  used[current_v] = true;

  int k1 = equation[current_v].first;
  int b1 = equation[current_v].second;

  for (size_t i = 0; i < g[current_v].size(); ++i) {
    int next_v = g[current_v][i].x;
    int current_w = g[current_v][i].w;
    if (!used[next_v]) {
      equation[next_v] = {current_w - k1, -b1};
      Dfs(next_v, used, equation, g);
    }
  }
}

bool CheckX(int x, std::vector<std::pair<int, int>>& equation, int n,
            std::vector<Three>& c) {
  std::vector<int> ans(n + 1);
  std::vector<int> copy(n);
  for (int i = 1; i <= n; ++i) {
    int res = equation[i].first + x * equation[i].second;
    if (!(1 <= res && res <= n)) {
      return false;
    }
    ans[i] = res;
    copy[i - 1] = res;
  }
  for (int i = 0; i < int(c.size()); ++i) {
    int s = ans[c[i].u] + ans[c[i].v];
    if (s != c[i].w) {
      return false;
    }
  }
  std::sort(copy.begin(), copy.end());
  for (size_t i = 0; i < copy.size(); ++i) {
    if (copy[i] != int(i) + 1) {
      return false;
    }
  }
  for (int i = 1; i <= n; ++i) {
    int res = equation[i].first + x * equation[i].second;
    std::cout << res << " ";
  }
  return true;
}

int main() {
  Init();
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<Node>> g(n + 1);
  std::vector<Three> c;

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
    c.push_back({u, v, w});
  }

  std::vector<bool> used(n + 1, false);
  std::vector<std::pair<int, int>> equation(n + 1);

  equation[1] = {0, 1};

  for (int i = 1; i <= n; ++i) {
    if (!used[i]) {
      Dfs(i, used, equation, g);
    }
  }

  int x1 = -1e9;
  int x2 = 1e9;

  for (int i = 1; i <= n; ++i) {
    int k = equation[i].first;
    int b = equation[i].second;
    if (b == 1) {
      x1 = std::max(x1, 1 - k);
    } else {
      x2 = std::min(x2, k - 1);
    }
  }

  if (CheckX(x1, equation, n, c)) {
    return 0;
  }
  CheckX(x2, equation, n, c);

  return 0;
}