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

ll FindMin(set<ll>& not_used, vvll& E, ll i) {
  ll min_value = INF;

  for (auto ind : not_used) {
    if (E[ind][i] < min_value) {
      min_value = E[ind][i];
    }
  }

  return min_value;
}

void solve() {
  ll n; cin >> n;
  vvll E(n, vll(n, -INF));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      cin >> E[i][j];
    }
  }

  set<ll> not_used;
  for (int i = 0; i < n; ++i) {
    not_used.insert(i);
  }

  ll i = 0;
  vll seq;

  while (i < n) {
    ll min_value = FindMin(not_used, E, i);
    set<ll> cand;
    for (auto ind : not_used) {
      if (E[ind][i] == min_value) {
        cand.insert(ind);
      }
    }
    int delta = 0;
    while (cand.size() > 1) {
      ++delta;
      ll min_value2 = FindMin(cand, E, i + delta);
      set<ll> new_cand;
      for (auto p : cand) {
        if (E[p][i + delta] == min_value2) {
          new_cand.insert(p);
        }
      }
      cand = new_cand;
    }
    seq.push_back(*cand.begin());
    not_used.erase(*cand.begin());
    i = *cand.begin() + 1;
  }

  for (auto p : not_used) {
    seq.push_back(p);
  }

  for (int i = seq.size() - 1; i >= 0; --i) {
    std::cout << seq[i] + 1 << " ";
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