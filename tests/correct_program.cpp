#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <optional>
#include <vector>

#include <set>

#include <unordered_map>

using std::cin, std::cout, std::optional, std::min, std::endl, std::pair,
    std::max, std::vector, std::set, std::swap, std::unordered_map;

struct WeightedEdge {
  int to;
  int64_t cost;
  WeightedEdge() = default;
  WeightedEdge(int a1, int64_t a2) {
    to = a1;
    cost = a2;
  }
};

bool operator<(const WeightedEdge& ft_edge, const WeightedEdge& sc_edge) {
  if (ft_edge.cost != sc_edge.cost) {
    return ft_edge.cost < sc_edge.cost;
  }
  return ft_edge.to < sc_edge.to;
}

struct Data {
  int pred, height, min_depth;
  bool used;
  Data() {
    pred = -1;
    height = -1;
    min_depth = -1;
    used = false;
  };
};

struct Dest {
  int to, num;
  Dest() = default;
  Dest(int to_i, int num_i) {
    to = to_i;
    num = num_i;
  }
};

struct Edge {
  int from, to, num;
  Edge() = default;
  Edge(int from_i, int to_i, int num_i) {
    from = from_i;
    to = to_i;
    num = num_i;
  }
};

struct Graph {
  static const int64_t max_vertexes = 2 * 1e6;
  int num_vertexes;
  int num_edges;
  vector<Data> data;
  vector<vector<Dest>> adj_list;
  set<Edge> bridges;
  Graph(int num_vertexes_i, int num_edges_i,
        const vector<vector<Dest>>& adj_list_i) {
    num_vertexes = num_vertexes_i;
    num_edges = num_edges_i;
    adj_list = adj_list_i;
    data.resize(num_vertexes);
  }
};

bool operator<(const Edge& ft_edge, const Edge& sc_edge) {
  return ft_edge.num < sc_edge.num;
}

void DFS(Graph& graph, int vertex, int pred = -1) {
  graph.data[vertex].used = true;
  if (pred == -1) {
    graph.data[vertex].height = graph.data[vertex].min_depth = 0;
  } else {
    graph.data[vertex].height = graph.data[pred].height + 1;
    graph.data[vertex].min_depth = graph.data[pred].height + 1;
  }
  for (auto & [ to, num ] : graph.adj_list[vertex]) {
    if (to == pred) {
      continue;
    }
    if (graph.data[to].used) {
      graph.data[vertex].min_depth =
          min(graph.data[vertex].min_depth, graph.data[to].height);
    } else {
      DFS(graph, to, vertex);
      graph.data[vertex].min_depth =
          min(graph.data[vertex].min_depth, graph.data[to].min_depth);
      if (graph.data[vertex].height < graph.data[to].min_depth) {
        graph.bridges.emplace(vertex, to, num);
      }
    }
  }
}

void Solve() {
  int num_vertexes, num_edges;
  cin >> num_vertexes >> num_edges;
  vector<vector<Dest>> adj_list(num_vertexes);
  for (int from, to, i = 0; i < num_edges; ++i) {
    cin >> from >> to;
    --from;
    --to;
    adj_list[from].emplace_back(to, i + 1);
    adj_list[to].emplace_back(from, i + 1);
  }
  Graph graph(num_vertexes, num_edges, adj_list);
  for (int vertex = 0; vertex < num_vertexes; ++vertex) {
    if (!graph.data[vertex].used) {
      DFS(graph, vertex);
    }
  }
  vector<int> ans;
  for (auto & [ from, to, num ] : graph.bridges) {
    int counter = 0;
    for (auto& dest : graph.adj_list[from]) {
      if (to == dest.to) {
        counter++;
      }
    }
    if (counter == 1) {
      ans.emplace_back(num);
    }
  }
  cout << ans.size() << endl;
  for (auto& i : ans) {
    cout << i << " ";
  }
}

signed main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Solve();
  return 0;
}