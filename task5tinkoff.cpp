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

std::random_device rd;
std::mt19937 gen(rd());

int random(long long low, long long high) {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

bool solve(ll n) {
  vll a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = rand() % 100 + 1;
  }

  sort(a.begin(), a.end());

  vll answers(n);

  for (int i = 0; i < n; ++i) {
    ll ans = a[i];
    for (int j = i + 1; j < n; ++j) {
      ans += (a[j] / a[i]) * a[i];
    }
    answers[i] = ans;
  }

  vll pref(n);

  bool pos = false;
  bool neg = false;

  for (int i = 1; i < n; ++i) {
    pref[i] = answers[i] - answers[i - 1];
  }

  for (int i = 0; i < n; ++i) {
    cout << answers[i] << " ";
  }
  cout << "\n\n\n";

  for (int i = 0; i < n; ++i) {
    bool ok = true;
    for (int j = 0; j < i; ++j) {
      if (pref[i] < 0) {
        ok = false;
        break;
      }
    }
    if (!ok) { continue; }
    for (int j = i; j < n; ++j) {
      if (pref[i] > 0) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return true;
    }
  }

  cout << "ERROR\n";

  for (int i = 0; i < n; ++i) {
    cout << a[i] << ' ';
  }
  cout << "\n\n\n";
  return false;

}

int main() {
  srand(time(NULL));
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 10000;
  // cin >> t;
  // cout << fixed << setprecision(10);
  
  while (t--) {
    solve(rand() % 10 + 1);
    // cout << solve() << endl;
    // if (solve(rand() % 100 + 1))
      //  cout << "OK" << endl;
  }

  return 0;
}