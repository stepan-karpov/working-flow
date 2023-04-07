#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Graph {
  const long long kKnostantFoo = 1e18;
  const long long kKnostantFoo2 = 100'000;
  long long vertex_num;
  std::vector<std::vector<long long>> graph;
  std::vector<std::vector<long long>> dp;
  std::vector<long long> dist;
  std::vector<int> parent;

  Graph(long long vertex_num) : vertex_num(vertex_num) {
    graph.assign(vertex_num, std::vector(vertex_num, kKnostantFoo));
    dp.assign(vertex_num, std::vector(vertex_num + 1, kKnostantFoo));
    parent.assign(vertex_num, -1);
    dist.assign(vertex_num, kKnostantFoo);
    for (int i = 0; i < vertex_num; ++i) {
      dp[i][0] = 0;
    }
  }

  void InputEdges() {
    for (int i = 0; i < vertex_num; ++i) {
      for (int j = 0; j < vertex_num; ++j) {
        std::cin >> graph[i][j];
        if (graph[i][j] == kKnostantFoo2) {
          graph[i][j] = kKnostantFoo;
        }
      }
    }
  }

  void FordBellman() {
    for (int k = 1; k <= vertex_num - 1; ++k) {
      for (int to = 0; to < vertex_num; ++to) {
        dp[to][k] = dp[to][k - 1];
        for (int mid = 0; mid < vertex_num; ++mid) {
          if (graph[mid][to] == kKnostantFoo ||
              dp[mid][k - 1] == kKnostantFoo) {
            continue;
          }
          if (dp[mid][k - 1] + graph[mid][to] < dp[to][k]) {
            parent[to] = mid;
            dp[to][k] = dp[mid][k - 1] + graph[mid][to];
          }
        }
      }
    }

    for (int to = 0; to < vertex_num; ++to) {
      long long haha = kKnostantFoo;
      for (int k = 0; k <= vertex_num - 1; ++k) {
        haha = std::min(haha, dp[to][k]);
      }
      dist[to] = haha;
    }
  }

  void Foo() {
    int k_long_name = vertex_num;
    for (int to = 0; to < vertex_num; ++to) {
      dp[to][k_long_name] = dp[to][k_long_name - 1];
      for (int mid = 0; mid < vertex_num; ++mid) {
        if (graph[mid][to] == kKnostantFoo ||
            dp[mid][k_long_name - 1] == kKnostantFoo) {
          continue;
        }
        if (dp[mid][k_long_name - 1] + graph[mid][to] < dp[to][k_long_name]) {
          parent[to] = mid;
          dp[to][k_long_name] = dp[mid][k_long_name - 1] + graph[mid][to];
        }
      }
    }

    int start = -1;

    for (int to = 0; to < vertex_num; ++to) {
      long long haha = dp[to][k_long_name];
      if (haha < dist[to]) {
        start = to;
      }
    }

    if (start == -1) {
      std::cout << "NO\n";
      return;
    }

    std::cout << "YES\n";

    std::vector<int> ans;
    std::set<int> added;

    // std::cout << start << "\n";

    ans.push_back(start);
    added.insert(start);

    int p_long_name = parent[start];

    while (added.find(p_long_name) == added.end()) {
      ans.push_back(p_long_name);
      added.insert(p_long_name);
      p_long_name = parent[p_long_name];
    }
    int cnt = 1;

    for (int i = int(ans.size()) - 1; i >= 0; --i) {
      ++cnt;
      // std::cout << ans[i] + 1 << " ";
      if (ans[i] == p_long_name) {
        break;
      }
    }

    std::cout << cnt << "\n";

    std::cout << p_long_name + 1 << " ";

    for (int i = int(ans.size()) - 1; i >= 0; --i) {
      std::cout << ans[i] + 1 << " ";
      if (ans[i] == p_long_name) {
        break;
      }
    }
  }
};

void Solve() {
  long long vertex_num;
  std::cin >> vertex_num;
  Graph gr(vertex_num);
  gr.InputEdges();
  gr.FordBellman();
  gr.Foo();
}

signed main() {
  Init();
  long long temp = 1;
  while (temp != 0) {
    Solve();
    --temp;
  }
  return 0;
}