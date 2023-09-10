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
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll n = 6;
vll sorted;
vll stat(4);

void output(vll& a) {
  for (int i = 0; i < a.size(); ++i) {
    cout << a[i] << " ";
  }
}

bool find(vll& a, ll v) {
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] == v) {
      return true;
    }
  }
  return false;
}

void sortFirst(vll& a) {
  sort(&a[0], &a[a.size() / 3 * 2]);
}

void sortSecond(vll& a) {
  sort(&a[a.size() / 3], &a[a.size()]);
}

ll cntAns(vll a) {
  vector<string> temp = {
    "000", "001", "010", "011",
    "100", "101", "110", "111",
  };
  ll ans = 1e9;
  for (int i = 0; i < temp.size(); ++i) {
    vll copy = a;
    for (ll p = 0; p < 3; ++p) {
      if (sorted == copy) {
        ans = min(ans, p);
      }
      if (temp[i][p] == '0') {
        sortFirst(copy);
      } else {
        sortSecond(copy);
      }
      if (sorted == copy) {
        ans = min(ans, p + 1);
      }
    }
  }
  return ans;
}

void backtrack(vll a) {
  if (a.size() == n) {
    ll s = cntAns(a);
    if (s == 3) {
      output(a);
      cout << " -> " << s << '\n';
    }
    ++stat[s];
    return;
  }
  for (int i = 1; i <= n; ++i) {
    if (!find(a, i)) {
      a.push_back(i);
      backtrack(a);
      a.pop_back();
    }
  }
}

void Solve() {
  for (int i = 1; i <= n; ++i) {
    sorted.push_back(i);
  }
  backtrack({});
  for (int i = 0; i < 4; ++i) {
    cout << i << ": " << stat[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;

  // freopen("input.txt", "w", stdout);
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