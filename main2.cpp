#include <string.h>

#include <iostream>
#include <map>
#include <vector>

long long res = 0;

void Input(int& n, std::vector<long long>& g) {
  std::cin >> n;
  int add = (n % 2);
  g.assign(n + add, 0);
  std::string s;
  for (int i = 0; i < n; ++i) {
    std::cin >> s;
    for (int j = 0; j < n; ++j) {
      if (s[j] > '0') {
        g[i] |= (1LL << j);
      }
    }
  }
  n += add;
  res = 1 - add;
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios::sync_with_stdio(false);
  int n;
  std::vector<long long> g;
  Input(n, g);
  std::map<int, int> logme;
  for (int i = 0; i < 30; ++i) {
    logme[(1LL << i)] = i;
  }
  int h = n / 2;
  int mx = (1 << h);
  int help[3][(1 << 25)] = {{0}};
  help[0][0] = help[1][0] = mx - 1;
  for (int mask = 1; mask < mx; ++mask) {
    int last = mask & -mask;
    help[0][mask] = help[0][mask ^ last] & (g[logme[last]] ^ last);
    help[1][mask] = help[1][mask ^ last] & (g[logme[last] + h] & (mx - 1));
    if ((help[0][mask] & mask) == mask) {
      help[2][mask] = 1;
    }
  }
  int zero = 0;
  for (int i = zero; i < h; ++i) {
    for (int mask = zero; mask < mx; ++mask) {
      if ((mask & (1 << i)) != zero) {
        help[2][mask] += help[2][mask ^ (1 << i)];
      }
    }
  }
  res += help[2][mx - 1];
  for (int mask = 1; mask < mx; ++mask) {
    int last = mask & -mask;
    help[0][mask] = help[0][mask ^ last] & ((g[logme[last] + h] >> h) ^ last);
    if ((help[0][mask] & mask) == mask) {
      res += help[2][help[1][mask]] + 1LL;
    }
  }
  std::cout << res;
}