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

void CreatePoly() {
  int n = random(1, 5);
  std::cout << n << " ";
  std::cout << random(0, 9) << " ";
  for (int i = 0; i < n; ++i) {
    std::cout << random(0, 9) << " ";
  }
  std::cout << "\n";
}

int main() {
  std::mt19937 mt(time(nullptr)); 
  int border = 5;

  int n = random(1, 10);
  std::cout << n << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << random(-border, border) << " " << random(-border, border) << "\n";
  }
  int q = random(4, 15);
  std::cout << q << "\n";
  for (int i = 0; i < q; ++i) {
    if (random(0, 1)) {
      std::cout << "get " << random(-border, border) << " " << random(-border, border) << "\n";
    } else {
      std::cout << "add " << random(-border, border) << " " << random(-border, border) << "\n";
    }
  }

  // int n = random(1, 1500);
  // std::cout << n << "\n";
  // for (int i = 0; i < n; ++i) {
  //   std::cout << random(-250, 250) << " " << random(-250, 250) << "\n";
  // }
  // int q = random(4, 1100);
  // std::cout << q << "\n";
  // for (int i = 0; i < q; ++i) {
  //   if (random(0, 1)) {
  //     std::cout << "get " << random(-250, 250) << " " << random(-250, 250) << "\n";
  //   } else {
  //     std::cout << "add " << random(-250, 250) << " " << random(-250, 250) << "\n";
  //   }
  // }
  return 0;
}