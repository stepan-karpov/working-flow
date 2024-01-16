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
  const std::string ALPH = "abcdefg";
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

int main() {
  std::mt19937 mt(time(nullptr)); 


  const std::string ALPH = "abcdefghijklmopq";
  int n = random(4, 5);
  int m = random(n, n * (n - 1) / 2);
  int q = 1000;

  std::cout << n << " " << m << " " << q << "\n";

  for (int i = 0; i < n; ++i) {
    cout << random(0, 10) << " ";
  }
  cout << "\n";

  set<pair<int, int>> used;

  for (int i = 0; i < m; ++i) {
    int u = random(0, n - 1);
    int v = random(0, n - 1);
    while (u == v || used.find({u, v}) != used.end()) {
      v = random(0, n - 1);
      u = random(0, n - 1);
    }
    used.insert({u, v});
    used.insert({v, u});
    cout << u + 1 << " " << v + 1 << "\n";
  }

  for (int i = 0; i < q; ++i) {
    if (random(0, 1)) {
      cout << "? " << random(1, n) << "\n";
    } else {
      cout << "+ " << random(1, n) << " " << random(1, 100) << "\n";
    }
  }


  return 0;
}