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

ll record = -1;
vvll ans = {{}};

ll cnt(vll& temp) {
  set<ll> a;

  for (int i = 1; i < temp.size(); ++i) {
    a.insert(temp[i] - temp[i - 1]);
  }
  return a.size();
}

void backtrack(ll k, ll n, vll temp) {
  if (temp.size() == n) {
    vll used = {};
    for (int i = 0; i < temp.size(); ++i) {
      if (temp[i]) {
        used.push_back(i + 1);
      }
    }
    if (used.size() != k) { return; }
    if (cnt(used) > record) {
      ans = {used};
      record = cnt(used);
    } else if (cnt(used) == record) {
      ans.push_back(used);
    }
    return;
  }
  temp.push_back(0);
  backtrack(k, n, temp);
  temp.pop_back();
  temp.push_back(1);
  backtrack(k, n, temp);
}

vll solve2(ll k, ll n) {
  vll ans;
  for (int i = 0; i < k; ++i) {
    ans.push_back(i + 1);
  }

  set<ll> diff;
  diff.insert(1);
  ans[k - 1] = n;

  for (int i = k - 1; i > 0; --i) {
    ll cur_d = 1;
    while (diff.find(cur_d) != diff.end()) {
      ++cur_d;
    }
    ll cur_best = ans[i] - cur_d;

    if (cur_best <= ans[i - 1]) {
      break;
    }
    ans[i - 1] = cur_best;
    diff.insert(cur_d);
  }

  return ans;
}

void Solve() {
  ll k = rand() % 15;
  ll n = rand() % 10 + k;
  backtrack(k, n, {});
  cout << k << " " << n << " " << record << '\n';
  // bool f = false;
  // vll my_ans = solve2(k, n);
  // for (int i = 0; i < ans.size(); ++i) {
  //   if (ans[i] == my_ans) { f = true; }
  // }
  // if (!f) {
  //   cout << k << ' ' << n << '\n';
  // } else {
  //   cout << "OK\n"; 
  // }
}



int main() {
  srand(time(NULL));
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // freopen("output.txt", "w", stdout);
  ll t = 10;
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