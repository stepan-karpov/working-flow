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

bool isPrime(int n){
  if (n == 1) { return false; }
  if (n == 2) { return true; }
  bool f = true;
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0){
      f = false;
      break;
    }
  }
  return f;   
}

bool FindIn(vll& temp, ll x) {
  for (int i = 0; i < temp.size(); ++i) {
    if (temp[i] == x) { return true; }
  }
  return false;
}

ll MEX(vll& temp, ll l, ll r) {
  for (int i = 1; i <= temp.size() + 10; ++i) {
    bool ok = true;
    for (int j = l; j <= r; ++j) {
      if (temp[j] == i) {
        ok = false;
        break;
      }
    }
    if (ok) { return i; }
  }
  return -1;
}

ll CheckPrim(vll& temp) {
  ll n = temp.size();

  ll cnt = 0;

  for (int l = 0; l < n; ++l) {
    for (int r = l; r < n; ++r) {
      ll mex = MEX(temp, l, r);
      if (isPrime(mex)) {
        ++cnt;
      }
    }
  }
  return cnt;
}

set<vll> ans;
ll best = 0;

void backtrack(vll temp, ll n) {
  if (temp.size() == n) {
    ll cur = CheckPrim(temp);
    if (cur > best) {
      ans.clear(); ans.insert(temp);
      best = cur;
    } else if (cur == best) {
      ans.insert(temp);
    }

    return;
  }
  for (int i = 1; i <= n; ++i) {
    if (!FindIn(temp, i)) {
      temp.push_back(i);
      backtrack(temp, n);
      temp.pop_back();
    }
  }
}

void solve() {
  ll n; cin >> n;

  backtrack({}, n);

  cout << best << "\n";

  ll cnt = 0;

  for (auto a : ans) {
    ++cnt;
    // if (cnt > 100) { continue; }
    for (int j = 0; j < a.size(); ++j) {
      cout << a[j] << " ";
    }
    cout << "\n";
  }

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  // cin >> t;
  // cout << fixed << setprecision(10);
  
  freopen("a.out", "w", stdout);

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