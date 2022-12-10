#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Column {
  long long a, b, c;
  Column(long long a, long long b, long long c) : a(a), b(b), c(c) {}
};

const long long MOD = 1e9 + 7;

int main() {
  Init();
  int n;
  std::cin >> n;
  std::vector<Column> table(n, {0, 0, 0});

  table[0].b = 1;

  for (int i = 1; i < n; ++i) {
    table[i].a = (table[i - 1].a + table[i - 1].b) % MOD;
    table[i].b = (table[i - 1].a + table[i - 1].b + table[i - 1].c) % MOD;
    table[i].c = (table[i - 1].b + table[i - 1].c) % MOD;
  }

  long long s = table[n - 1].a + table[n - 1].b + table[n - 1].c;

  std::cout << (s % MOD) << '\n';
  return 0;
}