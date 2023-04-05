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

int main() {
  std::mt19937 mt(time(nullptr)); 


  ll n = random(1, 5);
  ll m = random(n, n * (n + 1) / 2);
  ll s = random(1, n);
  ll t = random(1, n);


  cout << n << " " << m;
  cout << " " << s << " " << t << "\n";

  for (int i = 0; i < s; ++i) {
    cout << random(1, n) << " ";
  }
  cout << "\n";
  for (int i = 0; i < t; ++i) {
    cout << random(1, n) << " ";
  }

  set<pair<int, int>> q;

  for (int i = 0; i < m; ++i) {
    int u = random(1, n);
    int v = random(1, n);
    if (u < v) {
      std::swap(u, v);
    }
    while (u == v || q.find({u, v}) != q.end()) {
      u = random(1, n);
      v = random(1, n);
    }
    cout << u << " " << v << "\n";
    q.insert({u, v});
  }

  // for (int i = 0; i < n; ++i) {
  //   std::cout << random(0, 1000) << " ";
  // }

  return 0;
}