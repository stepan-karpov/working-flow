#include <ctime>
#include <iostream>
#include <random>

int Binpow(int num, const int kMod, int steps) {
  if (steps == 0) {
    return 1;
  }
  if ((steps & 1) == 1) {
    int temp = Binpow(num, kMod, steps - 1) % kMod;
    return (1LL * temp * num) % kMod;
  }
  int temp = Binpow(num, kMod, steps >> 1) % kMod;
  return (1LL * temp * temp) % kMod;
}

std::pair<int, int> BinPolynoms(std::pair<int, int> polynom, int mod, int pow,
                                int aa) {
  if (pow == 0) {
    return {0, 1};
  }
  if ((pow & 1) == 1) {
    std::pair<long long, long long> temp =
        BinPolynoms(polynom, mod, pow - 1, aa);
    long long part = temp.first * polynom.first * aa;
    part %= mod;
    temp.first = temp.first * polynom.second + temp.second * polynom.first;
    temp.second *= polynom.second;
    temp.second += part;
    temp.first %= mod;
    temp.second %= mod;
    return temp;
  }
  std::pair<long long, long long> temp =
      BinPolynoms(polynom, mod, pow >> 1, aa);
  long long part = temp.first * temp.first * aa;
  part %= mod;
  temp.first = 2 * temp.first * temp.second;
  temp.second *= temp.second;
  temp.second += part;
  temp.first %= mod;
  temp.second %= mod;
  return temp;
}

int FindRoot(int aa, int pp) {
  std::mt19937 mt(time(nullptr));
  while (true) {
    int ind = mt() % (pp - 1) + 1;
    std::pair<int, int> polynom{1, ind};
    std::pair<int, int> remainder = BinPolynoms(polynom, pp, (pp - 1) / 2, aa);
    remainder.second += (pp - 1);
    remainder.second %= pp;
    if (remainder.first != 0) {
      long long root =
          (1LL * remainder.second * Binpow(remainder.first, pp, pp - 2)) % pp;
      if ((root * root) % pp == aa) {
        return root;
      }
    }
  }
}

int main() {
  int aa;
  int pp;
  int tests;
  std::cin >> tests;
  while (tests != 0) {
    --tests;
    std::cin >> aa >> pp;
    if (pp == 2 || aa == 0) {
      std::cout << aa << "\n";
    } else if (Binpow(aa, pp, (pp - 1) / 2) != 1) {
      std::cout << "IMPOSSIBLE\n";
      continue;
    } else {
      int ans1 = FindRoot(aa, pp);
      int ans2 = pp - ans1;
      std::cout << std::min(ans1, ans2) << "\n";
    }
  }
}