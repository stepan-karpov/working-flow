#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

bool found_cycle = false;
std::vector<int> sequence;

void Dfs(int vertex, std::vector<int>& colors, std::vector<std::set<int>>& e) {
  if (found_cycle) {
    return;
  }
  if (colors[vertex] != -1) {
    return;
  }

  colors[vertex] = 1;

  for (auto v : e[vertex]) {
    if (colors[v] == 1) {
      found_cycle = true;
    } else {
      Dfs(v, colors, e);
    }
  }

  sequence.push_back(vertex);

  colors[vertex] = 2;
}

void Input(std::vector<std::set<int>>& e, int m) {
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    e[u].insert(v);
  }
}

int main() {
  Init();
  int n, m;
  std::cin >> n >> m;

  std::vector<std::set<int>> e(n);

  Input(e, m);

  std::vector<int> colors(n, -1);

  for (int i = 0; i < n; ++i) {
    if (colors[i] == -1) {
      Dfs(i, colors, e);
    }
  }

  if (found_cycle) {
    std::cout << "-1\n";
    return 0;
  }

  for (int i = int(sequence.size()) - 1; i >= 0; --i) {
    std::cout << sequence[i] + 1 << " ";
  }

  return 0;
}