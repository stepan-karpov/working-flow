#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Init();
  int k;
  std::cin >> k;

  std::vector<int> a(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> c(k + 1);
  for (int i = 1; i <= k; ++i) {
    std::cin >> c[i];
  }

  std::vector<int> p(k, 0);

  for (int i = 0; i < k; ++i) {
    p[i] = a[i];
    for (int j = 0; j <= std::min(k, i); ++j) {
      p[i] -= a[i - j] * c[j];
    }
  }

  while (!p.empty() && p[p.size() - 1] == 0) {
    p.pop_back();
  }
  std::cout << p.size() - 1 << '\n';

  for (int i = 0; i < p.size(); ++i) {
    std::cout << p[i] << ' ';
  }
  std::cout << '\n';
  std::cout << '\n';

  std::cout << k << '\n' << 1 << ' ';
  for (int i = 1; i <= k; ++i) {
    std::cout << -c[i] << " ";
  }
  std::cout << '\n';

  return 0;
}