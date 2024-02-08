#include <iostream>
using namespace std;

using ll = long long;

int main() {
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  ll c = 0;
  for (ll i = 0; i < 1e11; ++i) {
    ++c;
  }
  cout << c << "\n";

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  return 0;
}