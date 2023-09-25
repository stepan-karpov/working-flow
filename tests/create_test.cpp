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
  const std::string ALPH = "0123456789";
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

  int n = random(10, 15);
  int k = random(2, n);

  std::cout << n << " " << k << "\n";

  std::vector<string> added;

  for (int i = 0; i < n; ++i) {
    int chance = random(1, 5);
    if (added.size() == 0 || chance == 1) {
      added.push_back(CreateString(random(50, 100)));
      std::cout << added[added.size() - 1] << "\n";
    } else {
      int rand = random(0, added.size() - 1);
      int sz = added[rand].size();
      int l = random(1, sz);
      string cur = added[rand].substr(0, l)  + added[rand].substr(0, l);
      std::cout << cur << "\n";
      added.push_back(cur);
    }
  }
  int testcases = 100;
  std::cout << testcases << "\n";
  for (int i = 0; i < testcases; ++i) {
    std::cout << i << "\n";
  }

  return 0;
}