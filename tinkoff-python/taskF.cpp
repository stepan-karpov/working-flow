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

const ll INF = 1e9;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

string possible(ll med, ll n, ll s, vector<pll>& a) {
  ll less = 0;
  ll more = 0;
  ll sum_taken = 0;
  vector<pll> rest;
  for (int i = 0; i < n; ++i) {
    if (a[i].second < med) {
      ++less;
      sum_taken += a[i].first;
    } else if (a[i].first > med) {
      ++more;
      sum_taken += a[i].first;
    } else {
      rest.push_back(a[i]);
    }
  }
  if (less > n / 2) {
    return "to much";
  }
  if (more > n / 2) {
    return "to small";
  }
  if (sum_taken > s) {
    return "to much";
  }
  for (int i = 0; i < rest.size(); ++i) {
    if (less < n / 2) {
      ++less;
      sum_taken += rest[i].first;
    } else {
      ++more;
      sum_taken += med;
    }
    if (sum_taken > s) {
      return "to much";
    }
  }
  return "ok";
}

void solve() {
  ll n, s; cin >> n >> s;
  vector<pll> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }

  sort(a.begin(), a.end());

  ll l = -1;
  ll r = INF;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (possible(m, n, s, a) == "to much") {
      r = m;
    } else {
      l = m;
    }
  }

  std::cout << l << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  // cin >> t;
  // cout << fixed << setprecision(10);
  
  while (t--) {
    solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}