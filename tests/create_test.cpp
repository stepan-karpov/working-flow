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
  ll m = random(1, n);

  std::cout << n << " " << m << "\n";


  for (int i = 0; i < n; ++i) {
    std::cout << random(1, 1e5) << " ";
  }

  std::cout << "\n";
  std::vector<int> u;
  for (int i = 0; i < m; ++i) {
    u.push_back(random(1, 1e5));
  }
  std::sort(u.begin(), u.end());

  for (int i = 0; i < m; ++i) {
    std::cout << u[i] << " ";
  }

  for (int i = 0; i < m - 1; ++i) {
    if (u[i] > u[i + 1]) {
      cout << "jopa\n";
    }
  }

  // for (int i = 0; i < n; ++i) {
  //   std::cout << random(0, 1000) << " ";
  // }

  return 0;
}