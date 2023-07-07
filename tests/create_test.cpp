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
  // const std::string ALPH = "abcd";
  const std::string ALPH = "0123456789";
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

  ll n = random(10000, 10000);

  cout << n << "\n";

  for (int i = 0; i < n; ++i) {
    long long t1 = abs(random(1e7, 1e9));
    long long t2 = abs(random(1e7, 1e9));
    cout <<  t1 * t2 << "\n";
  }

  return 0;
}