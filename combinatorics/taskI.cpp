#include <iostream>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int64_t p;

int64_t binPow(int64_t a, int64_t x) {
  if (x == 0) {
    return 1;
  }
  if (x % 2 == 0) {
    int64_t temp = binPow(a, x / 2);
    return (temp * temp) % p;
  }
  return (a * binPow(a, x - 1)) % p;
}

int64_t factmod(int64_t n, int64_t p) {
	int64_t res = 1;
	while (n > 1) {
		res = (res * ((n/p) % 2 ? p-1 : 1)) % p;
		for (int64_t i=2; i<=n%p; ++i)
			res = (res * i) % p;
		n /= p;
	}
	return res % p;
}

int main() {
  Init();
  int64_t n;
  std::cin >> n >> p;
  // int64_t base = (n / p);
  // int64_t rem = (n % p);
  // int64_t ans = 1;
  // for (int i = 1; i < p; ++i) {
  //   int64_t power = base + (rem >= i);
  //   int64_t d = binPow(i, power) % p;
  //   ans *= d;
  //   ans %= p;
  // }
  // std::cout << ans << '\n';

  std::cout << factmod(n, p) << '\n';

  return 0;
}