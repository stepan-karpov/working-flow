#include <bits/stdc++.h>
using namespace std;
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,avx,tune=native")
// #pragma GCC optimize("fast-math")
// #pragma GCC optimize(2)
// #pragma GCC optimize("Ofast","inline","-ffast-math")
// #pragma GCC optimize "-O3"

using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

std::vector<long long> extendedGCD(long long a, long long b) {
  if (a == 0) {
    return {0, 1, b};
  }
  std::vector<long long> answer = extendedGCD(b % a, a);
  return {
    answer[1] - (b / a) * answer[0],
    answer[0],
    answer[2]
  };
}

void Solve() {
  long long a, b, n, m;
  cin >> a >> b >> n >> m;

  vll answer = extendedGCD(n, m);

  if (abs(b - a) % answer[2] != 0) {
    cout << "NO" << '\n';
    return; 
  }

  ll gcd = answer[2];

  std::cout << "YES ";
  ll x = -answer[0] * n * ((a - b) / gcd) + a;
  ll p = n * m / gcd;
  x %= p;
  x = (x + p) % p;
  std::cout << x << " " << p << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  cin >> t;
  // cout << fixed << setprecision(10);
  
  while (t--) {
    Solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}