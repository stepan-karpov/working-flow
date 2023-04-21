#include <bits/stdc++.h>
using namespace std;

using ll = long long;

std::random_device rd;
std::mt19937 gen(rd());

// returns random value from [low, high]
int random(long long low, long long high) {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

std::string CreateString(int size) {
  const std::string ALPH = "abcd";
  std::string ans = "";

  for (int i = 0; i < size; ++i) {
    ans += ALPH[random(0, ALPH.size() - 1)];
  }

  return ans;
}

bool is_prime(int n){
  bool f = true;
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0){
      f = false;
      break;
    }
  }
  return f;   
}

const int GraphINF = 1e9;

std::vector<std::vector<int>> GenerateGraph(int n, int m) {
  bool no_loops = true; // без петель
  bool no_even = true; // без кратных ребер
  std::vector<std::vector<int>> g(n, std::vector<int>(n, GraphINF));
  for (int i = 0; i < m; ++i) {
    int u = random(0, n - 1);
    int v = random(0, n - 1);
    if (no_loops) {
      while (g[u][v] != GraphINF || u == v) {
        u = random(0, n - 1);
        v = random(0, n - 1);
      }
    } else {
      while (g[u][v] != GraphINF) {
        u = random(0, n - 1);
        v = random(0, n - 1);
      }
    }
    g[u][v] = random(-10, 10);
  }
  return g;
}

void dfs(int cur_v, std::vector<std::vector<int>>& g, std::vector<bool>& used) {
  used[cur_v] = true;
  for (int i = 0; i < g.size(); ++i) {
    if (g[cur_v][i] == GraphINF) {
      continue;
    }
    if (!used[i]) {
      dfs(i, g, used);
    }
  }
}

bool isConnected(int a, int b, std::vector<std::vector<int>>& g) {
  // comp is a vector of vertexes that need to be achievable
  // starts is a vector of vertexes where we can start our path
  std::vector<bool> used(g.size(), false);
  dfs(a, g, used);
  if (used[b]) {
    return true;
  }
  return false;
}

int main() {
  std::mt19937 mt(time(nullptr)); 


  while (true) {
    ll n = random(2, 4);
    ll k = random(2, n + (n == 1));
    ll m = random(n - 1, n * (n - 1) / 2 + (n == 1));
    std::vector<std::vector<int>> g = GenerateGraph(n, m);
    std::vector<int> path;
    std::set<int> used;
    for (int i = 0; i < k; ++i) {
      int u = random(0, n - 1);
      // while (used.find(u) != used.end()) {
        // u = random(0, n - 1);
      // }
      path.push_back(u);
      used.insert(u);
    }
    bool ok = true;
    for (int i = 0; i < path.size() - 1; ++i) {
      if (!isConnected(path[i], path[i + 1], g)) {
        ok = false;
        break;
      }
    }
    if (!ok) {
      continue;;
    }
    std::cout << n << " " << m << " " << k << "\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (g[i][j] != GraphINF) {
          std::cout << i + 1 << " " << j + 1 << " " << g[i][j] << "\n";
        }
      }
    }
    for (int i = 0; i < k; ++i) {
      std::cout << path[i] + 1 << " ";
    }
    break;
  }


  return 0;
}