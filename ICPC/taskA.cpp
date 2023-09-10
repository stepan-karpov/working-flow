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

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef long double ld;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

struct Eq {
  int cy, s, dir;
  Eq(int cy, int s, int dir) : cy(cy), s(s), dir(dir) {}
};

void Solve() {
  ll n, m, k;
  std::cin >> n >> m >> k;
  vector<pll> a(k);
  vll ans(k, -1);
  map<int, vll> sums;
  map<int, vll> subs;

  for (int i = 0; i < k; ++i) {
    int x, y;
    cin >> x >> y;
    a[i] = {x, y};
    if (sums.find(x + y) == sums.end()) {
      sums[x + y] = {i};
    } else {
      sums[x + y].push_back(i);
    }
    if (subs.find(x - y) == subs.end()) {
      subs[x - y] = {i};
    } else {
      subs[x - y].push_back(i);
    }
  }


  Eq cur = {-1, 0, 1};
  ll time = 0;
  pll pnt = {0, 0};

  while (true) {

    // mark all points
    if (cur.cy == 1) {
      if (sums.find(cur.s) != sums.end()) {
        for (int i = 0; i < sums[cur.s].size(); ++i) {
          int to = sums[cur.s][i];
          if (ans[to] == -1) {
            int to_x = a[to].first;
            ans[to] = time + abs(to_x - pnt.first);
          }
        }
        sums[cur.s].clear();
      }
    } else {
      if (subs.find(cur.s) != subs.end()) {
        for (int i = 0; i < subs[cur.s].size(); ++i) {
          int to = subs[cur.s][i];
          if (ans[to] == -1) {
            int to_x = a[to].first;
            ans[to] = time + abs(to_x - pnt.first);
          }
        }
        subs[cur.s].clear();
      }
    }

    if (cur.dir == 1) {
      int y_n = (cur.s - n) / cur.cy;
      int x_m = cur.s - cur.cy * m;

      if (y_n < m) {
        time += abs(pnt.first - n);
        pnt = {n, y_n};
        cur = Eq(1, n + y_n, 4);
      } else if (y_n == m) {
        break;
      } else {
        time += abs(pnt.first - x_m);
        pnt = {x_m, m};
        cur = Eq(1, x_m + m, 2);
      }

    } else if (cur.dir == 2) {
      int y_n = (cur.s - n) / cur.cy;
      int x_m = cur.s;

      if (y_n > 0) {
        time += abs(pnt.first - n);
        pnt = {n, y_n};
        cur = Eq(-1, n - y_n, 3);
      } else if (y_n == 0) {
        break;
      } else {
        time += abs(pnt.first - x_m);
        pnt = {x_m, 0};
        cur = Eq(-1, x_m - 0, 1);
      }

    } else if (cur.dir == 3) {
      int y_n = (cur.s) / cur.cy;
      int x_m = cur.s;

      if (y_n > 0) {
        time += abs(pnt.first);
        pnt = {0, y_n};
        cur = Eq(1, 0 + y_n, 2);
      } else if (y_n == 0) {
        break;
      } else {
        time += abs(pnt.first - x_m);
        pnt = {x_m, 0};
        cur = Eq(1, x_m + 0, 4);
      }

    } else {
      int y_n = (cur.s) / cur.cy;
      int x_m = cur.s - cur.cy * m;

      if (y_n < m) {
        time += abs(pnt.first);
        pnt = {0, y_n};
        cur = Eq(-1, 0 - y_n, 1);
      } else if (y_n == m) {
        break;
      } else {
        time += abs(pnt.first - x_m);
        pnt = {x_m, m};
        cur = Eq(-1, x_m - m, 3);
      }
    }
  }

  for (int i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << " ";
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