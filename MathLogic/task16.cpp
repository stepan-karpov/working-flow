#include <iostream>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

bool SchaeffersStroke(bool x, bool y) {
  return (x + y != 2);
}

bool F(std::vector<int> a) {
  if (a.size() == 1) {
    return a[0];
  }
  std::vector<int> p1, p2;
  for (int i = 0; i < a.size() / 2; ++i){
    p1.push_back(a[i]);
  }
  for (int i = a.size() / 2; i < a.size(); ++i) {
    p2.push_back(a[i]);
  }
  return SchaeffersStroke(F(p1), F(p2));
}

int main() {
  Init();

  int c = 4;
  int cnt_zeros = 0;
  int cnt_ones = 0;
  for (int n = c; n <= c; ++n) {
    int value = (1 << n);
    std::cout << n << " : \n";
    for (int i = 0; i < (1 << value); ++i) {
      std::vector<int> cur_vector;
      // if (i > 100) {
      //   break;
      // }
      for (int j = value - 1; j >= 0; --j) {
        bool t = (i >> j) & 1;
        cur_vector.push_back(t);
        std::cout << t;
      }
      std::cout << ": ";
      int res = F(cur_vector);
      if (res == 0) {
        ++cnt_zeros;
      } else {
        ++cnt_ones;
      }
      std::cout << res << '\n';
    }
  }

  std::cout << "0: " << cnt_zeros << '\n';
  std::cout << "1: " << cnt_ones << '\n';

  return 0;
}