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

  int nums = 5;
  int range = 10;
  std::cout << nums << " " << 0 << '\n';

  for (int i = 0; i < nums; ++i) {
    std::cout << random(2, range) << ' ';
  }
  std::cout << '\n';

  int size = nums;
  int tests = 10;
  std::cout << tests << '\n';

  for (int i = 0; i < tests; ++i) {
    int border = 0;
    // if (size >= 3) {
    //   border = 1;
    // }
    int cmd = random(0, border);
    if (cmd == 0) {
      std::cout << "2 " << random(1, size) << '\n';
    } else {
      std::cout << "1 " << random(1, size) << '\n';
      --size;
    }
  }
  
  return 0;
}