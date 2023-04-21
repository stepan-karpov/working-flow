#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int to;
  int time;
  int cost;

  Edge(int to, int time, int cost) : to(to), time(time), cost(cost) {}
};

void DoStuff(int ti, int ver, Edge& edge,
             std::vector<std::vector<long long>>& dp,
             std::vector<std::vector<std::pair<int, int>>>& upd) {
  if (ti - edge.time >= 0 &&
      dp[edge.to][ti - edge.time] + edge.cost < dp[ver][ti]) {
    dp[ver][ti] = dp[edge.to][ti - edge.time] + edge.cost;
    upd[ver][ti] = {edge.to, ti - edge.time};
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n_artur;
  int m_artur;
  int t_artur;
  int first;
  int second;
  int time;
  int cost;
  const long long kInf = 1e18;
  std::cin >> n_artur >> m_artur >> t_artur;
  std::vector<std::vector<Edge>> adj(n_artur);
  for (int i = 0; i < m_artur; ++i) {
    std::cin >> first >> second >> cost >> time;
    adj[first - 1].push_back(Edge(second - 1, time, cost));
    adj[second - 1].push_back(Edge(first - 1, time, cost));
  }
  std::vector<std::vector<long long>> dp(
      n_artur, std::vector<long long>(t_artur + 1, kInf));
  std::vector<std::vector<std::pair<int, int>>> upd(
      n_artur, std::vector<std::pair<int, int>>(t_artur + 1, {-1, -1}));
  for (int i = 0; i <= t_artur; ++i) {
    dp[0][i] = 0;
  }
  for (int ti = 0; ti <= t_artur; ++ti) {
    for (int j = 0; j < 2; ++j) {
      for (int ver = 1; ver < n_artur; ++ver) {
        if (ti >= 1 && j == 0) {
          dp[ver][ti] = dp[ver][ti - 1];
          upd[ver][ti] = upd[ver][ti - 1];
        }
        for (Edge edge : adj[ver]) {
          DoStuff(ti, ver, edge, dp, upd);
        }
      }
    }
  }
  if (dp[n_artur - 1][t_artur] < kInf) {
    std::cout << dp[n_artur - 1][t_artur] << '\n';
    std::pair<int, int> cur = {n_artur - 1, t_artur};
    std::vector<int> ans;
    while (cur.first >= 0) {
      ans.push_back(cur.first);
      cur = upd[cur.first][cur.second];
    }
    std::cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
      std::cout << ans[ans.size() - 1 - i] + 1 << " ";
    }
    std::cout << '\n';
  } else {
    std::cout << -1 << '\n';
  }
}
