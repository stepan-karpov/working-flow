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
  std::string s;
  std::cin >> s;

  std::vector<int> prefix_function(s.size());

  prefix_function[0] = 0;

  for (int i = 1; i < s.size(); ++i) {
    int last_ans = prefix_function[i - 1];
    while (last_ans > 0 && s[last_ans] != s[i]) {
      last_ans = prefix_function[last_ans - 1];
    }
    if (s[last_ans] == s[i]) {
      ++last_ans;
    }
    prefix_function[i] = last_ans;
  }

  for (int i = 0; i < s.size(); ++i) {
    std::cout << prefix_function[i] << " ";
  }
  std::cout << "\n";


  return 0;
}