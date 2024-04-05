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

  for (int i = 0; i < 4; ++i) {
    cout << random(1, 300) << "\n";
  }


  return 0;
}