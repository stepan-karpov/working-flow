#include <algorithm>
#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void PrefixFunction(std::vector<int>& prefix_function, std::string& text) {
  prefix_function[0] = 0;

  for (int i = 1; i < text.size(); ++i) {
    int last_ans = prefix_function[i - 1];
    while (last_ans > 0 && text[last_ans] != text[i]) {
      last_ans = prefix_function[last_ans - 1];
    }
    if (text[last_ans] == text[i]) {
      ++last_ans;
    }
    prefix_function[i] = last_ans;
  }
}

void Solve() {
  int n_size;
  std::cin >> n_size;
  std::vector<std::string> dict(n_size);
  for (int i = 0; i < n_size; ++i) {
    std::cin >> dict[i];
  }
  std::string answer = dict[0];

  for (int i = 1; i < n_size; ++i) {
    int start = std::max(int(answer.size() - dict[i].size()), 0);
    
    std::string current_string = dict[i] + "#" + answer.substr(start, answer.size() - start);
    std::vector<int> prefix_function(current_string.size());
    PrefixFunction(prefix_function, current_string);

    int border = answer.size() - start;

    int to_delete = prefix_function[prefix_function.size() - 1];

    answer += dict[i].substr(to_delete, dict[i].size() - to_delete);
  }

  std::cout << answer << "\n";
}

int main() {
  Init();
  Solve();
  return 0;
}