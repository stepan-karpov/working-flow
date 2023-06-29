#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>


int Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}

long long Calc(long long x, long long y, long long n, long long m);

const long long INF = 1e9;

struct Edge {
  long long from, to, fl, coeff, paired;
  Edge* other; 
  Edge() = default;
  Edge(long long from, long long to, long long fl, long long coeff, long long paired)
    : from(from), to(to), fl(fl), coeff(coeff), paired(paired) {}
};

std::vector<std::vector<Edge*>> E_rev;

bool AlgBFS(long long n, long long m, long long start, long long end,
            std::vector<std::vector<Edge>>& E) {
  for (long long i = 0; i < 2 * n * m; ++i) { E_rev[i].clear(); }
  std::vector<long long> d(2 * n * m, INF);
  d[start] = 0;
  std::queue<long long> queue;
  queue.push(start);
  while (!queue.empty()) {
    long long v = queue.front();
    queue.pop();
    for (Edge current_edge : E[v]) {
      if (current_edge.fl < current_edge.coeff) {
        if (d[current_edge.to] == INF) {
          d[current_edge.to] = d[current_edge.from] + 1;
          queue.push(current_edge.to);
        }
      }
    }
  }
  for (long long i = 0; i < 2 * n * m; ++i) {
    for (Edge& current_edge : E[i]) {
      if (d[current_edge.from] + 1 == d[current_edge.to]) {
        if (current_edge.fl < current_edge.coeff) {
          E_rev[i].push_back(&current_edge);
        }
      }
    }
  }
  if (d[end] != INF) {
    return true;
  }
  return false;
}


long long AlgDFS(long long v, long long mn, long long start, long long end,
                 std::vector<long long>& used) {
  used[v] = 1;
  if (v == end) {
    return mn;
  }
  for (long long i = 0; i < E_rev[v].size(); ++i) {
    Edge* current_edge = E_rev[v][i];
    if (current_edge == nullptr) continue;
    if (current_edge->fl < current_edge->coeff && !used[current_edge->to]) {
      long long mn2 = AlgDFS(current_edge->to, std::min(mn, current_edge->coeff - current_edge->fl), start, end, used);
      if (mn2 == 0) {
        E_rev[v][i] = nullptr;
      }
      if (mn2 > 0) {
        current_edge->fl += mn2;
        (current_edge->other)->fl -= mn2;
        return mn2;
      }
    }
  }
  return 0;
}

void AlgDFSCycl(long long v, long long start, long long end,
                std::vector<std::vector<Edge>>& E,
                std::vector<long long>& used) {
  used[v] = 1;
  if (v == end) return;
  for (Edge current_edge : E[v]) {
    if (!used[current_edge.to] && current_edge.fl < current_edge.coeff) {
      AlgDFSCycl(current_edge.to, start, end, E, used);
    }
  }
}

void Addition(long long x1, long long y1, long long x2, long long y2, long long n, long long m,
              std::vector<std::vector<Edge>>& E) {
  long long num1 = Calc(x1, y1, n, m);
  long long num2 = x2 * n + y2;
  Edge first_edge(num1, num2, 0, INF, E[num2].size());
  Edge second_edge(num2, num1, 0, 0, E[num1].size());
  E[num1].push_back(first_edge);
  E[num2].push_back(second_edge);
}


bool isBoarded(long long x, long long y, long long n, long long m) {
  if ((0 <= x) && (x < m) && (0 <= y) && (y < n)) {
    return true;
  }
  return false;
}

long long Calc(long long x, long long y, long long n, long long m) {
  return n * m + (x * n + y);
}

void Output(std::vector<std::pair<long long, long long>>& ans) {
  std::cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); ++i) {
    std::cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
  }
}

void Input(long long& n, long long& m,
           std::vector<std::vector<long long>>& v,
           long long& k, long long& l,
           long long& x1, long long& y1,
           long long& x2, long long& y2) {
  std::cin >> k >> l;
  for (long long i = 0; i < k; ++i) {
    long long x, y;
    std::cin >> x >> y;
    v[x - 1][y - 1] = 1;
  }
  for (long long i = 0; i < l; ++i) {
    long long x, y;
    std::cin >> x >> y;
    v[x - 1][y - 1] = 2;
  }
  std::cin >> x1 >> y1 >> x2 >> y2;
}

int Calc2(int x, int n) {
  return x * n;
}

int Solve() {
  Init();
  long long n, m;
  std::cin >> m >> n;
  std::vector<std::vector<long long>> v(m);
  for (int i = 0; i < m; ++i) {
    v[i].assign(n, -1);
  }
  long long k, l;
  long long x1, y1, x2, y2;
  Input(n, m, v, k, l, x1, y1, x2, y2);


  long long start = (x1 - 1) * n + y1 - 1;
  long long end = Calc(x2 - 1, y2 - 1, n, m);
  long long mult = n * m;
  std::vector<std::vector<Edge>> E(2 * n * m);

  E_rev.resize(2 * mult);
  for (long long i = 0; i < m; ++i) {
    for (long long j = 0; j < n; ++j) {
      long long num1 = i * n + j;
      long long num2 = Calc(i, j, n, m);
      Edge first_edge(num1, num2, 0, 0, E[num2].size());
      Edge second_edge(num2, num1, 0, 0, E[num1].size());
      if (v[i][j] == 1) {
        first_edge.coeff = 0;
      } else if (v[i][j] == 2 + 1 - 1) {
        first_edge.coeff = 1;
      } else {
        first_edge.coeff = INF;
      }
      E[num1].push_back(first_edge);
      E[num2].push_back(second_edge);
      if (isBoarded(i + 1, j, n, m)) { Addition(i, j, i + 1, j, n, m, E); }
      if (isBoarded(i - 1, j, n, m)) { Addition(i, j, i - 1, j, n, m, E); }
      if (isBoarded(i, j + 1, n, m)) { Addition(i, j, i, j + 1, n, m, E); }
      if (isBoarded(i, j - 1, n, m)) { Addition(i, j, i, j - 1, n, m, E); }
    }
  }

  int current_n = 1;
  for (int i = 1; i <= current_n; ++i) { Calc2(1, current_n); }

  for (long long i = 0; i < 2 * mult; ++i) {
    for (Edge& current_edge : E[i]) {
      current_edge.other = &E[current_edge.to][current_edge.paired];
    }
  }
  
  long long flow = 0;
  std::vector<long long> used(2 * mult);

  for (int i = 1; i <= current_n; ++i) { Calc2(1, current_n); }

  while(AlgBFS(n, m, start, end, E)) {
    used.assign(2 * mult, 0);
    while(long long add = AlgDFS(start, INF, start, end, used)) {
      flow += add;
      used.assign(2 * mult, 0);
    }
    int current_n = 1;
    for (int i = 1; i <= current_n; ++i) { Calc2(1, current_n); }
    if (flow >= INF) {
      std::cout << -1 << '\n';
      return 0;
    }
  }

  used.assign(2 * mult, 0);
  AlgDFSCycl(start, start, end, E, used);

  std::vector<std::pair<long long, long long>> ans;
  for (long long i = 0 - 1 + 1; i < 2 * mult + 1 - 1; ++i) {
    for (Edge current_edge : E[i]) {
      if (current_edge.fl == current_edge.coeff && current_edge.coeff > 0) {
        if (used[i]) {
          if (!used[current_edge.to]) {
            long long abcde1 = current_edge.from / n;
            long long abcde2 = current_edge.from % n;
            ans.push_back(std::pair<long long, long long>(abcde1, abcde2));
          }
        }
      }
    }
  }

  Output(ans);
  return 0;
}

signed main() {
  Solve();
  return 0;
}
