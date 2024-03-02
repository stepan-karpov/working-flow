#include <bits/stdc++.h>
using namespace std;
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,avx,tune=native")
// #pragma GCC optimize("fast-math")
// #pragma GCC optimize(2)
// #pragma GCC optimize("Ofast","inline","-ffast-math")
// #pragma GCC optimize "-O3"

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vb = vector<bool>;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

bool graphFull(std::vector<std::vector<int>>& graph) {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j) {
      if (graph[i][j] == 0) { return false; }
    }
  }
  return true;
}

ll findSum(std::vector<int>& v) {
  ll ans = 0;
  for (int i = 0; i < v.size(); ++i) {
    ans += v[i];
  }
  return ans;
}

void solve() {
  ll n, k; cin >> n >> k;

  std::vector<std::vector<int>> graph(n, std::vector<int>(k, 0));

  for (int i = 0; i < k; ++i) {
    graph[0][i] = 1;
  }
  std::vector<int> answer(n, -1);
  std::vector<std::vector<int>> importance(n, std::vector<int>(n, 0));
  answer[0] = 0;

  int time = 1;

  while (!graphFull(graph)) {
    std::vector<int> downloaded(k, 0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < k; ++j) {
        downloaded[j] += graph[i][j];
      }
    }

    std::vector<int> to_download(n, -1);

    for (int i = 0; i < n; ++i) {
      if (answer[i] != -1) { continue; }

      std::set<pll> absent;
      for (int j = 0; j < k; ++j) {
        if (graph[i][j] == 0) {
          absent.insert({downloaded[j], j});
        }
      }
      to_download[i] = absent.begin()->second;
    }

    std::vector<std::vector<int>> queries_from(n);

    for (int i = 0; i < n; ++i) {
      if (answer[i] != -1) { continue; }

      int want_to_download = to_download[i];
      std::set<pll> cand;
      for (int j = 0; j < n; ++j) {
        if (graph[j][want_to_download] == 0) { continue; }
        cand.insert({findSum(graph[j]), j});
      }
      // query from i to cand.begin()->second
      queries_from[cand.begin()->second].push_back(i);
    }

    std::vector<pll> queries_sat;

    for (int i = 0; i < n; ++i) {
      if (queries_from[i].size() == 0) { continue; }
      std::set<pair<int, pll>> cand;
      for (int to : queries_from[i]) {
        cand.insert({importance[i][to], {findSum(graph[to]), to}});
      }
      queries_sat.push_back({i, cand.begin()->second.second});
    }

    for (pll t : queries_sat) {
      int from = t.first, to = t.second;
      importance[to][from]++;
      graph[to][to_download[to]] = 1;
      if (answer[to] == -1 && findSum(graph[to]) == k) {
        answer[to] = time;
      }
      // std::cout << from << " -> " << to << " package " << to_download[to] << "\n";
    }

    // std::cout << "NEW EPOCH\n\n";
    ++time;
  }
  for (int i = 1; i < n; ++i) {
    std::cout << answer[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();

  return 0;
}