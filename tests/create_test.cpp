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
  const std::string ALPH = "abc";
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

  int testcases = random(100, 500);

  std::cout << testcases << "\n";

  set<string> used;

  for (int i = 0; i < testcases; ++i) {
    int type = random(1, 5);
    if (type == 1) {
      if (used.size() > 0) {
        cout << "- " << *used.begin() << "\n";
        used.erase(used.begin());
      } else {
        cout << "- " << CreateString(random(1, 3)) << "\n";
      }
    } else if (type == 2) {
      cout << "? " << CreateString(random(4, 5)) << "\n";
    } else {
      string temp = CreateString(random(1, 5));
      used.insert(temp);
      cout << "+ " << temp << "\n";
    }
  }

  return 0;
}