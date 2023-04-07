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

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef long double ld;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll getSum(int l, int r, vll& prefix_sum) {
  ll sum = prefix_sum[r];
  if (l != 0) {
    sum -= prefix_sum[l - 1];
  }
  return sum;
}

void Solve() {
  ll n, c, k; cin >> n >> c >> k;

  vll prefix_sum(n + 1, 0);
  vll a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  prefix_sum[0] = a[0];

  for (int i = 1; i < n; ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + a[i];
  }
  if (n <= k) {
    cout << getSum(0, n - 1, prefix_sum) << "\n";
  }
  for (int i = 0; i < min(c, n - k + 1); ++i) {
    std::cout << i << " " << i + k << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  // cin >> t;
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