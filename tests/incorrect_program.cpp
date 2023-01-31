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

void topological_sort(vector<set<ll>>& E, set<pll>& in,
                      vll& in_accordance, vvll& nums, vector<pll>& a,
                      vector<bool>& handled) {
  if (in.size() == 0) { return; }

  pll temp = *in.begin();
  if (temp.first != 0) { return; }

  ll current_vertex = temp.second;
  handled[current_vertex] = true;
  in.erase(temp);

  for (int i = 0; i < nums[current_vertex].size(); ++i) {
    ll cur_v = nums[current_vertex][i];
    if (!handled[cur_v]) {
      handled[current_vertex] = false;
      return;
    }
    a[current_vertex].first += a[cur_v].first;
    a[current_vertex].second += a[cur_v].second;
  }

  for (ll cur_v : E[current_vertex]) {
    ll current_in = in_accordance[cur_v];
    in.erase({current_in, cur_v});
    in.insert({current_in - 1, cur_v});
    --in_accordance[cur_v];
  }
  
  topological_sort(E, in, in_accordance, nums, a, handled);
}

void solve() {
  ll n; cin >> n;
  vvll nums(n + 1);
  vector<pll> a(n + 1, {0, 0});
  a[1] = {1, 0};
  a[2] = {0, 1};

  vll in_accordance(n + 1, 0);
  set<pll> in;
  vector<set<ll>> E(n + 1);

  for (int i = 3; i <= n; ++i) {
    ll k; cin >> k;
    for (int j = 0; j < k; ++j) {
      ll current_prev; cin >> current_prev;
      nums[i].push_back(current_prev);
      E[current_prev].insert(i);
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (ll cur_v : E[i]) {
      ++in_accordance[cur_v];
    }
  }

  for (int i = 1; i <= n; ++i) {
    in.insert({in_accordance[i], i});
  }

  vector<bool> handled(n + 1, false);

  topological_sort(E, in, in_accordance, nums, a, handled);

  // for (int i = 1; i <= n; ++i) {
  //   if (!handled[i]) {
  //     cout << '0';
  //   } else {
  //     cout << '1';
  //   }
  // }
  // cout << '\n';
  // cout << '\n';
  // cout << '\n';

  ll q; cin >> q;

  for (int i = 0; i < q; ++i) {
    ll x, y, s; cin >> x >> y >> s;
    if (!handled[s]) {
      cout << '0';
      continue;
    }
    if (a[s].first <= x && a[s].second <= y) {
      cout << '1';
    } else {
      cout << '0';
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