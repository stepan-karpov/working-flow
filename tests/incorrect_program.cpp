#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

std::random_device rd;
std::mt19937 gen(rd());

// returns random value from [low, high]
long long RandomLl(long long low, long long high) {
  std::uniform_int_distribution<long long> dist(low, high);
  return dist(gen);
}

int RandomInt(long long low, long long high) {
  std::uniform_int_distribution<int> dist(low, high);
  return dist(gen);
}

const long long kTreshhold = 1e9;
const int kMillerRabinIter = 600;
const std::vector<int> kPrimes = {2, 3, 5, 7};

__int128_t FindGcd(__int128_t first_value, __int128_t second_value) {
  if (first_value == static_cast<__int128_t>(0)) {
    return first_value;
  }
  if (first_value < second_value) {
    std::swap(first_value, second_value);
  }
  if (first_value % second_value == 0) {
    return second_value;
  }
  return FindGcd(second_value, first_value % second_value);
}

long long BinPow(long long aa, long long xx, __int128_t mod) {
  if (xx == 0) {
    return 1;
  }
  if (xx % 2 == 0) {
    __int128_t temp = BinPow(aa, xx / 2, mod);
    return static_cast<long long>((temp * temp) % mod);
  }
  __int128_t t1 = aa;
  __int128_t t2 = BinPow(aa, xx - 1, mod);
  return static_cast<long long>((t1 * t2) % mod);
}

int Brute(long long nn) {
  for (int i = 2; i * i <= nn; ++i) {
    if (nn % i == 0) {
      return i;
    }
  }
  return nn;
}

bool IsPrime(long long nn) {
  long long tt = nn - 1;
  long long ss = 0;
  while (tt % 2 == 0) {
    tt >>= 1;
    ++ss;
  }

  for (int i = 0; i < kMillerRabinIter; ++i) {
    long long aa = RandomLl(1, nn - 2);
    long long yy = 1;
    long long xx = BinPow(aa, tt, nn);
    for (long long j = 0; j < ss; ++j) {
      yy = static_cast<long long>(
          (static_cast<__int128_t>(xx) * static_cast<__int128_t>(xx)) % nn);
      bool cond = xx != nn - 1;
      cond &= (yy == 1);
      cond &= xx != 1;
      if (cond) {
        return false;
      }
      xx = yy;
    }
    if (yy - 1 != 0) {
      return false;
    }
  }
  return true;
}

long long Pollard(long long nn) {
  long long xx = RandomLl(1LL, nn - 1);
  long long yy = 1;
  long long ii = 0;
  long long stage = 2;

  long long dd = 1;
  long long precalc = std::gcd(nn, std::abs(xx - yy));
  while ((dd = precalc) == 1) {
    if (ii == stage) {
      yy = xx;
      stage <<= 1;
    }

    xx = static_cast<long long>(static_cast<__int128_t>(xx + 1) *
                                static_cast<__int128_t>(xx + 1) % nn);
    ++ii;
    precalc = std::gcd(nn, std::abs(xx - yy));
  }
  return dd;
}

void Factorize(long long nn, std::vector<long long>& dividers) {
  if (nn == 1) {
    return;
  }
  for (size_t i = 0; i < kPrimes.size(); ++i) {
    while (nn % kPrimes[i] == 0) {
      dividers.push_back(kPrimes[i]);
      nn /= kPrimes[i];
    }
  }
  if (nn <= kTreshhold) {
    while (nn > 1) {
      int div = Brute(nn);
      if (div != 1) {
        dividers.push_back(div);
      }
      nn /= div;
    }
  } else {
    if (IsPrime(nn)) {
      dividers.push_back(nn);
      return;
    }
    long long p1 = Pollard(nn);
    long long p2 = nn / p1;
    Factorize(p1, dividers);
    Factorize(p2, dividers);
  }
}

void Solve() {
  long long nn;
  std::cin >> nn;
  std::vector<long long> dividers;
  for (size_t i = 0; i < kPrimes.size(); ++i) {
    while (nn % kPrimes[i] == 0) {
      dividers.push_back(kPrimes[i]);
      nn /= kPrimes[i];
    }
  }
  Factorize(nn, dividers);
  std::sort(dividers.begin(), dividers.end());
  std::cout << dividers.size() << " ";
  for (size_t i = 0; i < dividers.size(); ++i) {
    std::cout << dividers[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  srand(time(nullptr));
  Init();
  int tests;
  std::cin >> tests;
  for (int i = 0; i < tests; ++i) {
    Solve();
  }
  return 0;
}