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
  const std::string ALPH = "ab";
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
  // int m = random(3, 5);
  int m = 2;

  cout << n << " " << m << "\n";

  for (int i = 0; i < n; ++i) {
    std::cout << random(1, m) << " ";
  }


  return 0;
}