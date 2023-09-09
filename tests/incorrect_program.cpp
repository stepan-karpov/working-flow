#include <iostream>
#include <string>
#include <vector>

std::vector<int> ZFunc(std::string str) {
  int n_size = str.size();
  std::vector<int> z_function(n_size);
  int left = -1;
  int right = -1;
  for (int i = 1; i < n_size; ++i) {
    if (left <= i && i <= right) {
      z_function[i] = std::min(z_function[i - left], right - i + 1);
    }
    while (i + z_function[i] < n_size &&
           str[z_function[i]] == str[i + z_function[i]]) {
      ++z_function[i];
    }
    if (i + z_function[i] - 1 > right) {
      left = i;
      right = i + z_function[i] - 1;
    }
  }
  return z_function;
}

void Solve() {
  std::string initial_string;
  std::cin >> initial_string;
  int n_size = initial_string.size();

  int ans = 1;

  for (int i = 0; i < n_size; ++i) {
    std::vector<int> z = ZFunc(initial_string.substr(i, n_size - i));
    for (int j = i; j < n_size - 1; ++j) {
      int potential_period = j - i + 1;
      int local_k = z[j - i + 1] / potential_period;
      ans = std::max(ans, local_k + 1);
    }
  }

  std::cout << ans << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solve();

  return 0;
}