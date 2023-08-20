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
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vb = vector<bool>;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

void Count1(vector<pll>& max_sequence_left, string& s) {
  ll n = s.size();
  ll current_zeros = 0;
  ll current_ones = 0;
  if (s[0] == '0') {
    max_sequence_left[0].second = 1;
    current_zeros = 1;
  } else {
    max_sequence_left[0].first = 1;
    current_ones = 1;
  }
  for (int i = 1; i < n; ++i) {
    if (s[i] == '0') {
      current_ones = 0;
      current_zeros += 1;
      max_sequence_left[i].second = max(max_sequence_left[i - 1].second, current_zeros);
    } else {
      current_zeros = 0;
      current_ones += 1;
      max_sequence_left[i].first = max(max_sequence_left[i - 1].first, current_ones);
    }
  }
}

void Count2(vector<pll>& max_sequence_left, string& s) {
  ll n = s.size();
  ll current_zeros = 0;
  ll current_ones = 0;
  if (s[n - 1] == '0') {
    max_sequence_left[n - 1].second = 1;
    current_zeros = 1;
  } else {
    max_sequence_left[n - 1].first = 1;
    current_ones = 1;
  }
  for (int i = n - 2; i >= 0; --i) {
    if (s[i] == '0') {
      current_ones = 0;
      current_zeros += 1;
      max_sequence_left[i].second = max(max_sequence_left[i + 1].second, current_zeros);
    } else {
      current_zeros = 0;
      current_ones += 1;
      max_sequence_left[i].first = max(max_sequence_left[i + 1].first, current_ones);
    }
  }
}

void solve() {
  ll n, k; cin >> n >> k;
  string s; cin >> s;
  vector<pll> max_sequence_left(n, {0, 0});
  vector<pll> max_sequence_right(n, {0, 0});
  Count1(max_sequence_left, s);
  Count2(max_sequence_right, s);  

  for (int a = 1; a <= n; ++a) {
    for (int l = 0; l < n; ++l) {
      for (int r = l; r < n; ++r) {
        if (r - l + 1 != k) {
          continue;
        }

        

      }
    }
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
    solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}