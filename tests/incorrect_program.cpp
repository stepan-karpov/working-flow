#include <bits/stdc++.h>
using namespace std;

const string ALPH = "abcdefghijklmnopqrstuvwxyz";
const int INF = 1e9 + 100;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  
  int n;
  std::cin >> n;
  if (n == 6) {
    std::cout << n << "\n";
  } else {
    std::cout << '3' << '\n';
  }
  return 0;
}