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

struct SegmentTree {
  struct Node {
    int sum = 0;
    int min = -1;
    int min_value = 1e9;
    bool push = false;

    Node(ll sum, ll min) : sum(sum) {}
  };
  
  int size = 1;
  std::vector<Node> tree;

  SegmentTree(int n) {
    while (size < n) {
      size *= 2;
    }
    tree.assign(2 * size - 1, 0);
  }

  void Rebuild(ll x) {
    if ()
  }

  ll get(ll l, ll r, ll lx, ll rx, ll x) {
    Rebuild(x);
    if (l <= lx && rx <= r) {
      return tree[x].sum;
    }
    ll m = (lx + rx) / 2;
    ll s1 = get(l, r, lx, m, 2 * x + 1);
    ll s2 = get(l, r, m, rx, 2 * x + 2);
    return s1 + s2;
  }

  ll get(ll l, ll r) {
    return get(l, r, 0, size, 0);
  }

};

struct Node {
  int d, r, ind;
  Node(ll d, ll r, ll ind) : d(d), r(r), ind(ind) {}
};

void Solve() {
  ll n, m; cin >> n >> m;

  SegTree a(m);

  for (int i = 0; i < m; ++i) {
    ll x; cin >> x;
    a.add(i, i + 1, x);
  }

  vector<Node> c(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i].d >> c[i].r >> c[i].ind;
  }

  vll ans(n, 0);

  std::sort(c.begin(), c.end());

  for (int i = 0; i < n; ++i) {
    a.add(0, m, -c[i].d);

    ll cur_min_ind = a.getMin(0, m);
    while (a.get(cur_min_ind, cur_min_ind + 1) < 0) {
      a.add(cur_min_ind, cur_min_ind + 1, -a.get(cur_min_ind, cur_min_ind + 1));
      cur_min_ind = a.getMin(0, m);
    }

    // ans = binarySearch()

    a.add(0, m, c[i].r);
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
    Solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}