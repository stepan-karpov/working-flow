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

pll cnt_need(ll s, vvll& nums, ll level) {
  if (s == 1) {
    return {1, 0};
  } else if (s == 2) {
    return {0, 1};
  }
  if (level > 100) {
    return {INF, INF};
  }
  pll ans = {0, 0};
  for (int i = 0; i < nums[s].size(); ++i) {
    pll cur_ans = cnt_need(nums[s][i], nums, level + 1);
    ans.first += cur_ans.first;
    ans.second += cur_ans.second;
  }
  return ans;
}

void solve() {
  ll n; cin >> n;
  vvll nums(n + 1);
  for (int i = 3; i <= n; ++i) {
    ll k; cin >> k;
    for (int j = 0; j < k; ++j) {
      ll x; cin >> x;
      nums[i].push_back(x);
    }
  }

  ll q; cin >> q;

  for (int i = 0; i < q; ++i) {
    ll x, y, s; cin >> x >> y >> s;
    pll cur_v = cnt_need(s, nums, 0);
    if (cur_v.first >= INF && cur_v.second >= INF) {
      cout << '0';
    } else {
      if (x >= cur_v.first && y >= cur_v.second) {
        cout << '1';
      } else {
        cout << '0';
      }
    }
  }
  cout << '\n';

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