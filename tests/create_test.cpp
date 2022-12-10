#include <bits/stdc++.h>

std::random_device rd;
std::mt19937 gen(rd());

// returns random value from [low, high]
int random(long long low, long long high) {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

std::string CreateString(int size) {
  const std::string ALPH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string ans = "";

  for (int i = 0; i < size; ++i) {
    ans += ALPH[random(0, ALPH.size() - 1)];
  }

  return ans;
}


int main() {
  std::mt19937 mt(time(nullptr)); 

  int tests = 5;
  int range = 50;
  std::cout << tests << '\n';

  int size = 0;
  std::vector<std::string> added;
  
  for (int i = 0; i < tests; ++i) {
    int border = 0;
    if (size > 3) {
      border = 5;
    }
    int t = random(0, border);
    if (t == 0) {
      std::cout << "insert " << random(0, range) << '\n';
      ++size;
    } else if (t == 1) {
      std::cout << "delete " << random(0, range) << '\n';
    } else if (t == 2) {
      std::cout << "exists " << random(0, range) << '\n';
    } else if (t == 3) {
      std::cout << "next " << random(0, range) << '\n';
    } else if (t == 4) {
      std::cout << "prev " << random(0, range) << '\n';
    } else if (t == 5) {
      std::cout << "kth " << random(0, size - 1) << '\n';
    }
  }
  
  return 0;
}