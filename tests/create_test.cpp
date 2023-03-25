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
  ll m = random(0, n * 2);

  std::cout << n << " " << m << "\n";

  std::set<std::pair<int, int>> used;

  for (int i = 0; i < n; ++i) {
    int u = random(1, n);
    int v = random(1, n);
    std::cout << u << " " << v << "\n";
  }



  // for (int i = 0; i < n; ++i) {
  //   std::cout << random(0, 1000) << " ";
  // }

  return 0;
}