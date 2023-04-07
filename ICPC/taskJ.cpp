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

  map<ll, pair<ll, ll>> coord = {{0, {-1, 0}},
                                 {1, {0, 1}},
                                 {2, {1, 0}},
                                 {3, {0, -1}},
                                };
bool ok(ll pos_x, ll pos_y, vector<string>& a, ll cur_vec) {

  ll new_x = pos_x + coord[cur_vec].first;
  ll new_y = pos_y + coord[cur_vec].second;

  int n = a.size();
  int m = a[0].size();

  if (new_x < 0 || new_x >= n) {
    return false;
  }
  
  if (new_y < 0 || new_y >= m) {
    return false;
  }

  if (a[new_x][new_y] != '*') { return true; }

  return false;


}

void Solve() {
  ll n, m;
  cin >> n >> m;
  vector<string> a(n);

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  ll pos_x = -1;
  ll pos_y = -1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == 'U' || a[i][j] == 'D' ||
          a[i][j] == 'R' || a[i][j] == 'L') {
        pos_x = i;
        pos_y = j;
      }
    }
  }

  int cur_vec = 0;
  if (a[pos_x][pos_y] == 'R') {
    cur_vec = 1;
  }
  if (a[pos_x][pos_y] == 'D') {
    cur_vec = 2;
  }
  if (a[pos_x][pos_y] == 'L') {
    cur_vec = 3;
  }

  vvll marked(n, vll(m, 0));

  for (int i = 0; i < 1e5; ++i) {
    marked[pos_x][pos_y] = 1;
    for (int j = 0; j < 10; ++j) {
      if (!ok(pos_x, pos_y, a, cur_vec)) {
        cur_vec = (cur_vec + 1) % 4;
      } else {
        pos_x = pos_x + coord[cur_vec].first;
        pos_y = pos_y + coord[cur_vec].second;
        marked[pos_x][pos_y] = 1;
        break;
      }
    }
  }

  ll ans = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ans += marked[i][j];
    }
  }

  cout << ans << "\n";

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