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
  const std::string ALPH = "abcdefghijklmopq";
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

  string text = CreateString(random(10, 15));
  // cout << text << "\n";

  int testcases = random(1, 2);

  cout << testcases << "\n";

  for (int i = 0; i < testcases; ++i) {
    int chance = random(0, 10);
    if (chance < 9) {
      int l = random(0, text.size() - 2);
      int r = random(l + 1, text.size() - 1);
      string cur = text.substr(l, r - l + 1);
      cout << cur << " ";
    } else {
      cout << CreateString(random(3, 4)) << " ";
    }
  }

  return 0;
}