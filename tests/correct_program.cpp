#include <algorithm>
#include <iostream>
#include <vector>
const int kInf = 2100000000;

struct Graph {
  int size_v;
  int size_e;
  int size_k;
  std::vector<std::vector<std::vector<int>>> edges = {};
  std::vector<std::vector<int>> next_v;
  std::vector<std::vector<int>> next_e;
  bool have_negative_cycle = false;
  std::vector<int> lections = {};
  std::vector<std::vector<std::vector<int>>> dp;
  Graph(int size_v, int size_e, int size_k)
      : size_v(size_v), size_e(size_e), size_k(size_k) {
    for (int index = 0; index < size_v; ++index) {
      edges.emplace_back();
    }
    dp = std::vector<std::vector<std::vector<int>>>(
        size_v + 1, std::vector<std::vector<int>>(
                        size_v + 1, std::vector<int>(size_v + 1, kInf)));
    next_v =
        std::vector<std::vector<int>>(size_v, std::vector<int>(size_v + 1, -1));
    next_e =
        std::vector<std::vector<int>>(size_v, std::vector<int>(size_v + 1, -1));
    for (int index = 0; index < size_e; ++index) {
      int from;
      int to;
      int weight;
      std::cin >> from >> to >> weight;
      edges[from - 1].push_back({to - 1, -weight, index});
    }
    for (int index = 0; index < size_k; ++index) {
      int town;
      std::cin >> town;
      lections.push_back(town - 1);
    }
  }
};

void FirstFloyd(Graph& graph) {
  for (int id = 1; id <= graph.size_v; ++id) {
    for (auto jd : graph.edges[id - 1]) {
      if (graph.dp[id][jd[0] + 1][0] > jd[1]) {
        graph.dp[id][jd[0] + 1][0] = jd[1];
        graph.next_e[id - 1][jd[0]] = jd[2];
        graph.next_v[id - 1][jd[0]] = jd[0];
      }
    }
  }
}
void Floyd(Graph& graph) {
  FirstFloyd(graph);
  for (int kk = 1; kk <= graph.size_v; ++kk) {
    for (int v_id = 1; v_id <= graph.size_v; ++v_id) {
      for (int u_id = 1; u_id <= graph.size_v; ++u_id) {
        if (graph.dp[v_id][kk][kk - 1] == kInf ||
            graph.dp[kk][u_id][kk - 1] == kInf) {
          graph.dp[v_id][u_id][kk] = graph.dp[v_id][u_id][kk - 1];
          continue;
        }
        graph.dp[v_id][u_id][kk] =
            std::min(graph.dp[v_id][kk][kk - 1] + graph.dp[kk][u_id][kk - 1],
                     graph.dp[v_id][u_id][kk - 1]);
        if (graph.dp[v_id][kk][kk - 1] + graph.dp[kk][u_id][kk - 1] <
            graph.dp[v_id][u_id][kk - 1]) {
          graph.next_e[v_id - 1][u_id - 1] = graph.next_e[v_id - 1][kk - 1];
          graph.next_v[v_id - 1][u_id - 1] = graph.next_v[v_id - 1][kk - 1];
        }
      }
    }
  }
  for (int start_id = 0; start_id < (int)graph.lections.size() - 1;
       ++start_id) {
    int start = graph.lections[start_id] + 1;
    int finish = graph.lections[start_id + 1] + 1;
    for (int middle = 1; middle <= graph.size_v; ++middle) {
      if (graph.dp[start][middle][graph.size_v] != kInf &&
          graph.dp[middle][finish][graph.size_v] != kInf &&
          graph.dp[middle][middle][graph.size_v] < 0) {
        graph.have_negative_cycle = true;
        return;
      }
    }
  }
}
void Solve() {
  int size_v;
  int size_e;
  int size_k;
  std::cin >> size_v >> size_e >> size_k;
  Graph graph(size_v, size_e, size_k);
  Floyd(graph);
  if (graph.have_negative_cycle) {
    std::cout << "infinitely kind";
  } else {
    int start = graph.lections[0];
    int finish = graph.lections[1];
    int cnt = 1;
    std::vector<int> ans = {};
    while (cnt < size_k) {
      int current = start;
      while (current != finish) {
        ans.push_back(graph.next_e[current][finish]);
        current = graph.next_v[current][finish];
      }
      start = finish;
      if (cnt < size_k - 1) {
        finish = graph.lections[cnt + 1];
      }
      ++cnt;
    }
    std::cout << ans.size() << "\n";
    for (int el : ans) {
      std::cout << el + 1 << " ";
    }
  }
}
int main() { Solve(); }