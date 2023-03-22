#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Init();
  int n = 4;
  
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    b[i] = a[i];
  }

  std::sort(b.begin(), b.end());

  bool straight = true, reverse = true;

  for (int i = 0; i < 4; ++i) {
    if (a[i] != b[i]) {
      straight = false;
    }
    if (a[i] != b[n - i - 1]) {
      reverse = false;
    }
  }

  if (straight || reverse) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }

  return 0;
}