#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#pragma GCC optimize("-Ofast,unroll-loops,fast-math")

const int MAXN = 1e7, MAXP = 5e6 + 8;

int primes[MAXP], lp[MAXN + 1], answer[MAXN + 1], hassq[MAXN + 1], primes2[20];

int getans(int m, int n) {
  int cnt = 0;
  int oldm = m;
  m /= lp[m];
  while (m > 1) {
    primes2[cnt] = lp[m];
    m /= lp[m];
    ++cnt;
  }
  int res = answer[oldm / lp[oldm]], coef, multipl;
  for (int mask = 0; mask < (1 << cnt); ++mask) {
    multipl = lp[oldm];
    coef = -1;
    for (int j = 0; j < cnt; ++j) {
      if (mask & (1 << j)) {
        coef *= -1;
        multipl *= primes2[j];
      }
    }
    res += coef * (n / multipl);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, cntpr = 0;
  cin >> n;
  answer[1] = n;
  long long sum = n;
  for (int i = 2; i <= n; ++i) {
    if (lp[i] == 0) {
      answer[i] = n - (n / i);
      lp[i] = i;
      if (i * i <= n) {
        primes[cntpr++] = i;
      }
    }
    sum += answer[i];
    for (int j = 0; j < cntpr && primes[j] <= lp[i] && i * primes[j] <= n; ++j) {
      lp[i * primes[j]] = primes[j];
      if (i % primes[j] == 0) {
        answer[i * primes[j]] = answer[i];
        hassq[i * primes[j]] = primes[j];
      } else {
        if (hassq[i]) {
          answer[i * primes[j]] = answer[(i / hassq[i]) * primes[j]];
          hassq[i * primes[j]] = hassq[i];
        } else {
          answer[i * primes[j]] = getans(i * primes[j], n);
        }
      }
    }
  }
  cout << sum;
}