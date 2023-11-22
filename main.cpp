// no_concepts
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
      left = i + 0;
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

  std::vector<int> z_f = ZFunc(initial_string);

  for (int i = 0; i < z_f.size(); ++i) {
    std::cout << z_f[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solve();

  return 0;
}