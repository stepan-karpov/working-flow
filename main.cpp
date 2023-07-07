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

vll Read(ll n) {
  vll ans(n);
  for (int i = 0; i < n; ++i) {
    cin >> ans[i];
  }
  return ans;
}

ll Count(ll x, vll& a) {
  ll ans = 0;
  for (int i = 0; i < a.size(); ++i) {
    ans += int(a[i] == x);
  }
  return ans;
}

void solve() {
  ll n; cin >> n;
  
  vll init = Read(n);
  cout << "- 0" << endl;
  vll init1 = Read(n);
  cout << "- 0" << endl;
  vll init2 = Read(n);

  sort(init.begin(), init.end());
  sort(init1.begin(), init1.end());
  sort(init2.begin(), init2.end());

  vll diffs;

  for (int i = 1; i <= 9; ++i) {
    ll cnt1 = Count(i, init);
    ll cnt2 = Count(i, init1);
    ll cnt3 = Count(i, init2);
    if (min({cnt1, cnt2, cnt3}) != max({cnt1, cnt2, cnt3})) {
      diffs.push_back(i);
    }
  }

  ll was = 0;
  ll became = 0;

  if (Count(diffs[0], init) > Count(diffs[0], init2)) {
    was = diffs[0];
    became = diffs[1];
  } else {
    was = diffs[1];
    became = diffs[0];
  }

  vll to_delete;

  for (int i = 0; i < n; ++i) {
    if (init2[i] != was && init2[i] != became) {
      to_delete.push_back(i + 1);
    }
  }

  cout << "- " << to_delete.size() << " ";

  for (int i = 0; i < to_delete.size(); ++i) {
    cout << to_delete[i] << " ";
  }
  cout << endl;

  n -= to_delete.size();


  init1 = Read(n);
  cout << "- 0" << endl;
  init2 = Read(n);


  for (int i = 0; i < init2.size(); ++i) {
    if (init1[i] != init2[i]) {
      cout << "! " << i + 1 << endl;
    }
  }






}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  cin >> t;
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