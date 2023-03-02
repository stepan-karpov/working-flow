#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

const long long mod = 1e9 + 7;

int main() {
  Init();
  int n;
  std::cin >> n;
  std::vector<long long> a(6, 0);
  a[1] = 1;

  for (int i = 0; i < n; ++i) {
    std::vector<long long> temp(6, 0);
    for (int j = 0; j < 6; ++j) {
      long long left = (j - 1 + 6) % 6;
      long long right = (j + 1) % 6;
      temp[j] = a[j] + a[left] + a[right] % mod;
    }
    a = temp;
  }
  std::cout << a[0] << '\n';

  return 0;
}