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
  const std::string ALPH = "0123456789";
  // const std::string ALPH = "abcdefghijklmopq";
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

void DFS(int v, vector<vector<int>>& g, vector<int>& kek) {
  kek[v] = true;
  for (auto& to : g[v]) {
    if (kek[to]) {
      continue;
    }
    DFS(to, g, kek);
  }
}


int main() {
  std::mt19937 mt(time(nullptr)); 

  int n = random(3, 5);
  int m = random(n, n * (n - 1) / 2);

  std::cout << n << " " << m << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << random(2, 2) << " ";
  }
  std::cout << "\n";
  
  set<std::pair<int, int>> edges;
  vector<int> hui(n, 0);
  vector<vector<int>> g(n);

  while (edges.size() != m) {
    int u = random(0, n - 1);
    int v = random(0, n - 1);
    if (u > v) { swap(u, v); }
    while (u == v) {
      u = random(0, n - 1);
      v = random(0, n - 1);
      if (u > v) {
        swap(u, v);
      }
    }
    edges.insert({u, v});
  }

  for (auto& [i, j] : edges) {
    g[i - 1].emplace_back(j - 1);
    g[j - 1].emplace_back(i - 1);
  }


  
  DFS(0, g, hui);
  auto kek = [&hui, &n]() {
    for (int i = 0; i < n; ++i) {
      if (hui[i] == false) {
        return false;
      }
    }
    return true;
  };
    while (!kek()) {
      g.clear();
      g.resize(n);
      hui.assign(n, 0);
      while (edges.size() != m) {
      int u = random(0, n - 1);
      int v = random(0, n - 1);
      if (u > v) { swap(u, v); }
      while (u == v) {
        u = random(0, n - 1);
        v = random(0, n - 1);
        if (u > v) {
          swap(u, v);
        }
      }
      edges.insert({u, v});
    }

    for (auto& [i, j] : edges) {
      g[i - 1].emplace_back(j - 1);
      g[j - 1].emplace_back(i - 1);
    } 
  }
  for (auto el : edges) {
    std::cout << el.first + 1 << " " << el.second + 1 << "\n";
  }

  return 0;
}