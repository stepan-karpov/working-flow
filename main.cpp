#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int U, D, teleport_i, teleport_j;
int last_deck = 1e3 - 1;
std::vector<std::vector<std::pair<int, int>>> g;

void InputTeleports(int sss) {
  std::set<int> used;
  used.insert(sss);
  used.insert(last_deck);
  used.insert(0);
  int l;
  std::cin >> l;
  std::vector<int> cur(1e3 + 1);
  for (int i = 0; i < l; ++i) {
    int k;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      std::cin >> cur[j];
      --cur[j];
      used.insert(cur[j]);
    }
    for (int j = 0; j < k; ++j) {
      for (int h = 0; h < k; ++h) {
        if (j == h) { continue; }
        g[cur[j]].push_back({cur[h], teleport_i + teleport_j});
        g[cur[h]].push_back({cur[j], teleport_i + teleport_j});
      }
    }
  }
  auto it = used.begin();
  auto end = used.end();
  --end;
  --end;
  while (it != end) {
    int l1 = *it;
    ++it;
    int l2 = *it;
    --it;
    g[l1].push_back({l2, U * (l2 - l1)});
    g[l2].push_back({l1, D * (l2 - l1)});
    ++it;
  }
}

void Dijkstra(int sss) {

  std::vector<int> dist(last_deck + 10, 1e9);
  std::set<std::pair<int, int>> qu;

  qu.insert({0, 0});

  while(!qu.empty()) {
    int cur_v = qu.begin()->second;
    int cur_dist = qu.begin()->first;
    qu.erase(qu.begin());

    for (size_t i = 0; i < g[cur_v].size(); ++i) {
      int to = g[cur_v][i].first;
      int new_dist = cur_dist + g[cur_v][i].second;
      if (dist[to] > new_dist) {
        qu.erase({dist[to], to});
        dist[to] = new_dist;
        qu.insert({dist[to], to});
      }
    }
  }

  std::cout << dist[sss] << "\n";

}

int main() {
  Init();
  g.resize(last_deck + 10);
  int end;
  std::cin >> end;
  --end;
  std::cin >> U >> D >> teleport_i >> teleport_j;

  InputTeleports(end);
  Dijkstra(end);

  return 0;
}