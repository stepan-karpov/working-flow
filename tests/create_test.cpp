#include <bits/stdc++.h>
using namespace std;

using ll = long long;

std::random_device rd;
std::mt19937 gen(rd());

// returns random value from [low, high]
long long random(long long low, long long high) {
  std::uniform_int_distribution<long long> dist(low, high);
  return dist(gen);
}

std::string CreateString(int size) {
  const std::string ALPH = "a";
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

  int n = 1;
  std::cout << n << "\n";
  for (int i = 0; i < n; ++i) {
    long long t = random(1, 1e18);
    if (random(0, 1)) {
      t %= int(1e9);
    }
    std::cout << t << " ";
  }
  std::cout << "\n";
  return 0;
}