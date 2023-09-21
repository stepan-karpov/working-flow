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

int main() {
  std::mt19937 mt(time(nullptr)); 

  int n = random(2, 4);
  int m = random(2, 4);

  std::cout << n << " " << m << "\n";

  for (int i = 0; i < n; ++i) {
    std::cout << CreateString(m) << "\n";
  }

  int a = random(1, 2);
  int b = random(1, 2);

  std::cout << a << " " << b << "\n";

  for (int i = 0; i < a; ++i) {
    std::cout << CreateString(b) << "\n";
  }

  return 0;
}