
#include <map>
#include <iostream>
int main() {
  std::map<int, int> m;
  for (int i = 0; i < 5; ++i) {
    m[i] = i + 1;
  }

  auto left = m.lower_bound(3);
  auto right = m.upper_bound(4);
  std::cout << left->first << "\n";
  std::cout << right->first << "\n";
  // left->second = right->second = 0;
  // for (auto item: m) {
    // std::cout << item.second;
  // }
}