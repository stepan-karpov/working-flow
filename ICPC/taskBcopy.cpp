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

struct Node {
  int t, s, f;
  Node(int t, int s, int f) : t(t), s(s), f(f) {}
};

void Solve() {
  ll n;
  cin >> n;

  vector<Node> a(n, {0, 0, 0});

  for (int i = 0; i < n; ++i) {
    cin >> a[i].t;
    cin >> a[i].s;
    cin >> a[i].f;
  }
  
  vll ans(n, 0);

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {

      Node a1 = a[i];
      Node a2 = a[j];

      if (a1.t > a2.t) {
        swap(a1, a2);
      }

      ll delta_t = a2.t - a1.t;

      if (a1.s < a1.f) {
        ll new_pos = a1.s + delta_t;
        if (new_pos > a1.f) {
          continue;
        }
        a1.t = a2.t;
        a1.s = new_pos;
      } else {
        ll new_pos = a1.s - delta_t;
        if (new_pos < a1.f) {
          continue;
        }
        a1.t = a2.t;
        a1.s = new_pos;
      }

      if (a1.s == a2.s) {
        ++ans[i];
        ++ans[j];
        continue;
      }

      ll dir1 = 1;
      if (a1.f < a1.s) { dir1 = -1; }

      ll dir2 = 1;
      if (a2.f < a2.s) { dir2 = -1; }

      if (dir1 == dir2) {
        continue;
      }

      if (a1.s > a1.f) {
        swap(a1, a2);
      }

      ll l1 = a1.s;
      ll r1 = a1.f;
      ll l2 = a2.f;
      ll r2 = a2.s;

      if (r2 < l1 || r1 < l2) { continue; }

      bool t1 = (2 * a1.f >= a1.s + a2.s);
      bool t2 = (2 * a2.f <= a1.s + a2.s);

      if (t1 && t2) {
        ++ans[i];
        ++ans[j];
        continue;
      }

    }
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << " ";
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
    Solve();
    // cout << solve() << endl;
    // if (solve())
    //    cout << "Yes" << endl;
    // else
    //    cout << "No" << endl;
  }

  return 0;
}