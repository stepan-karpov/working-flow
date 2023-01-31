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


void find_cycles(vector<set<ll>>& E, vector<bool>& in_cycle, vll& mark, ll current_vertex, vll& current_parent) {

  mark[current_vertex] = 1;

  for (ll current_v : E[current_vertex]) {
    if (mark[current_v] == 0) {
      current_parent[current_v] = current_vertex;
      find_cycles(E, in_cycle, mark, current_v, current_parent);
    } else if (mark[current_v] == 1) {
      ll cur_v = current_vertex;
      while (cur_v != current_v) {
        in_cycle[cur_v] = true;
        cur_v = current_parent[cur_v];
      }
      in_cycle[current_vertex] = true;
      in_cycle[current_v] = true;
    }
  }

  mark[current_vertex] = 2;
}

void solve() {
  // ll n; cin >> n;
  vector<pll> a(n + 1, {0, 0});
  a[1] = {1, 0};
  a[2] = {0, 1};

  vector<set<ll>> E(n + 1);

  for (int i = 3; i <= n; ++i) {
    // ll k; cin >> k;
    set<ll> adj;
    for (int j = 0; j < k; ++j) {
      ll current_number; cin >> current_number;
      a[i].first += a[current_number].first;
      a[i].second += a[current_number].second;
      E[current_number].insert(i);
    }
  }


  vector<bool> in_cycle(n + 1, 0);
  vll mark(n + 1, 0);
  vll current_parent(n + 1, -1);

  for (int i = 1; i <= n; ++i) {
    if (mark[i] == 0) {
      find_cycles(E, in_cycle, mark, i, current_parent);
    }
  }

  ll q; cin >> q;

  for (int i = 0; i < q; ++i) {
    ll A, B, S; cin >> A >> B >> S;
    if (in_cycle[S]) {
      cout << "0";
      continue;
    }
    if (a[S].first <= A && a[S].second <= B) {
      cout << "1";
    } else {
      cout << "0";
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