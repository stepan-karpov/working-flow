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

struct SegTree {
  int size = 1;
  struct Node {
    int value = 0;
    bool state = false;
    bool propagate = false;
    Node() : value(0), state(false), propagate(false) {}
  };
  vector<Node> tree;

  SegTree(int n) {
    while (size < n) {
      size *= 2;
    }
    tree.assign(2 * size - 1, Node());
  }

  void InitializeNode(int value, bool state, int ind, int lx, int rx, int x) {
    Propagate(x, lx, rx);
    if (rx - lx == 1) {
      tree[x].state = state;
      tree[x].value = state ? value : 0;
      return;
    }
    ll m = (lx + rx) / 2;
    if (ind < m) {
      InitializeNode(value, state, ind, lx, m, 2 * x + 1);
    } else {
      InitializeNode(value, state, ind, m, rx, 2 * x + 2);
    }
    tree[x].value = tree[2 * x + 1].value ^ tree[2 * x + 2].value;
  }


  void Propagate(int x, int lx, int rx) {
    if (!tree[x].propagate) { return; }
    if (rx - lx == 1) {
      tree[x].state = !tree[x].state;
      tree[x].value ^= tree[x].value;
      tree[x].propagate = false;
      return;
    }
    tree[x].propagate = false;
    Node& c1 = tree[2 * x + 1];
    Node& c2 = tree[2 * x + 2];

    c1.propagate = true;
    c2.propagate = true;
  }

  void ReverseSegment(int l, int r, int lx, int rx, int x) {
    if (l <= lx && rx <= r) {
      return 
    }
  }


};

void solve() {
  ll n; cin >> n;
  vll a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  string s; cin >> s;
  SegTree seg_tree(n);
  for (int i = 0; i < n; +i) {
    seg_tree.InitializeNode(a[i], s[i] == '1', i, 0, 2 * seg_tree.size - 1, 0);
  }

  ll q; cin >> q;
  for (int i = 0; i < q; ++i) {
    ll type; cin >> type;
    if (type == 1) {
      ll l, r; cin >> l >> r; --l;
      seg_tree.ReverseSegment(l, r, 0, 2 * seg_tree.size - 1, 0);
    } else {
      cout << seg_tree.tree[0].value << " ";
    }
  }
  cout << "\n";

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