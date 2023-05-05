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

bool check1(vll& diff1, vll& diff2) {
  ll n = diff1.size();

  for (int i = 0; i < n; ++i) {
    if (diff1[i] != diff2[i]) {
      return false;
    }
  }
  return true;
}

bool check2(vll& diff1, vll& diff2) {
  ll n = diff1.size();

  for (int i = 0; i < n; ++i) {
    if (diff1[(i + 1) % n] != diff2[i % n]) {
      return false;
    }
  }
  return true;
}

bool check3(vll& diff1, vll& diff2) {
  ll n = diff1.size();

  for (int i = 0; i < n; ++i) {
    if (diff1[(i - 1 + n) % n] != diff2[i % n]) {
      return false;
    }
  }
  return true;
}

bool solve() {
  ll n; cin >> n;
  vll a1(n);
  for (int i = 0; i < n; ++i) {
    cin >> a1[i];
  }
  std::sort(a1.begin(), a1.end());

  vll a2(n);
  for (int i = 0; i < n; ++i) {
    cin >> a2[i];
  }
  std::sort(a2.begin(), a2.end());

  vll diff1;
  for (int i = 1; i < n; ++i) {
    diff1.push_back(a1[i] - a1[i - 1]);
  }
  diff1.push_back(a1[0] + 360000 - a1[n - 1]);
  vll diff2;
  for (int i = 1; i < n; ++i) {
    diff2.push_back(a2[i] - a2[i - 1]);
  }
  diff2.push_back(a2[0] + 360000 - a2[n - 1]);

  // std::cout << "\n\n\n";
  // for (int i = 0; i < diff1.size(); ++i) {
  //   std::cout << diff1[i] << " ";
  // }
  // std::cout << "\n";
  // for (int i = 0; i < diff2.size(); ++i) {
  //   std::cout << diff2[i] << " ";
  // }
  // std::cout << "\n\n\n";
  if (check1(diff1, diff2)) return true;
  if (check2(diff1, diff2)) return true;
  if (check3(diff1, diff2)) return true;

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  // cin >> t;
  // cout << fixed << setprecision(10);
  
  while (t--) {
    // solve();
    // cout << solve() << endl;
    if (solve())
       cout << "possible" << endl;
    else
       cout << "impossible" << endl;
  }

  return 0;
}