#include <algorithm>
#include <iostream>
#include <vector>

const int kInf = 2e9;

struct Graph {
  int size_v;
  int size_e;
  int max_t;
  struct Node {
    int index;
    int tt;
    int pp;
    Node(int index, int pp, int tt) : index(index), tt(tt), pp(pp) {}
  };
  std::vector<std::vector<std::vector<int>>> prev = {};
  std::vector<std::vector<int>> dp = {};
  std::vector<std::vector<Node>> edges = {};
  Graph(int size_v, int size_e, int max_t) 
      : size_v(size_v), size_e(size_e), max_t(max_t) {
    prev = std::vector<std::vector<std::vector<int>>>(
               size_v, std::vector<std::vector<int>>(max_t + 1, {kInf, -1}));
    dp = std::vector<std::vector<int>>(
             size_v, std::vector<int>(max_t + 1, kInf));
    edges = std::vector<std::vector<Node>>(size_v);
    for (int i = 0; i <= max_t; ++i) {
      dp[0][i] = 0;
    }
    for (int i = 0; i < size_e; ++i) {
      int uu;
      int vv;
      int w123;
      int w234;
      std::cin >> uu >> vv >> w234 >> w123;
      --uu;
      --vv;
      edges[uu].push_back(Node(vv, w234, w123));
      edges[vv].push_back(Node(uu, w234, w123));
    }
  }
  void Solve() {
    const int my_var = 13;
    for (int time = 0; time <= max_t; ++time) {
      for (int round = 0; round < 2; ++round) {
        for (int index = 1; index < size_v; ++index) {
          if (time >= 1 && round == 0) {
            prev[index][time] = prev[index][time - 1];
            dp[index][time] = dp[index][time - 1];
          }

          for (Node edge : edges[index]) {
            if (time - edge.tt >= 0 &&
                dp[index][time] > dp[edge.index][time - edge.tt] + edge.pp) {
              prev[index][time] = {edge.index, time - edge.tt};
              dp[index][time] = dp[edge.index][time - edge.tt] + edge.pp;
            }
          }
        }
      }
    }
    if (dp[size_v - 1][max_t] == kInf) {
      std::cout << -1 << '\n';
    } else {
      std::cout << dp[size_v - 1][max_t] << '\n';
      std::vector<int> current = {size_v - 1, max_t};
      std::vector<int> ans;
      while (current[0] > 0 && (int) ans.size() < size_v) {
        ans.push_back(current[0]);
        current = prev[current[0]][current[1]];
      }
      ans.push_back(current[0]);
      std::cout << ans.size() << '\n';
      std::reverse(ans.begin(), ans.end());
      for (int an : ans) {
        std::cout << an + 1 << " ";
      }
    }
  }
};


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int size_v;
  int size_e;
  int max_t;
  std::cin >> size_v >> size_e >> max_t;
  Graph graph = Graph(size_v, size_e, max_t);
  graph.Solve();
}