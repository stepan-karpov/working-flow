#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> g;
  std::vector<bool> used;
  std::vector<int> tin;
  std::vector<int> ret;
  std::set<std::pair<int, int>> single;
  std::set<std::pair<int, int>> doubled;
  std::vector<bool> is_bridge;
  int timer = 0;

  void InputGraph() {
    std::cin >> n >> m;
    g.assign(n, std::vector<std::pair<int, int>>());
    used.assign(n, false);
    tin.assign(n, -1);
    ret.assign(n, 0);
    is_bridge.assign(m, false);
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u;
      --v;
      if (single.find({std::min(u, v), std::max(v, u)}) != single.end()) {
        doubled.insert({std::min(u, v), std::max(v, u)});
      }
      single.insert({std::min(u, v), std::max(v, u)});
      g[u].push_back({v, i});
      g[v].push_back({u, i});
    }
  }

  void DfsForBridges(int current_vertex, int parent) {
    tin[current_vertex] = timer++;
    ret[current_vertex] = tin[current_vertex];
    used[current_vertex] = true;
    for (size_t i = 0; i < g[current_vertex].size(); ++i) {
      int to = g[current_vertex][i].first;
      int num = g[current_vertex][i].second;
      if (to == parent) {
        continue;
      }
      if (used[to]) {
        ret[current_vertex] = std::min(ret[current_vertex], tin[to]);
      } else {
        DfsForBridges(to, current_vertex);
        ret[current_vertex] = std::min(ret[current_vertex], ret[to]);
        if (ret[to] == tin[to]) {
          is_bridge[num] = true;
        }
      }
    }
  }

  void FindBridges() {
    for (int i = 0; i < n; ++i) {
      if (!used[i]) {
        DfsForBridges(i, -1);
      }
    }
  }

  void OutputBridges() {
    std::set<int> ans;
    for (int i = 0; i < n; ++i) {
      for (size_t j = 0; j < g[i].size(); ++j) {
        int u = i;
        int v = g[i][j].first;
        int num = g[i][j].second;
        if (is_bridge[num] &&
            doubled.find({std::min(u, v), std::max(v, u)}) == doubled.end()) {
          ans.insert(num);
        }
      }
    }
    std::cout << ans.size() << "\n";
    for (auto el : ans) {
      std::cout << el + 1 << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  Init();
  Graph g;
  g.InputGraph();
  g.FindBridges();
  g.OutputBridges();
  return 0;
}