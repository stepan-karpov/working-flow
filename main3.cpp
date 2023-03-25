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
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

struct Node {
  ll x, y, num;
  Node(ll x, ll y, ll num) : x(x), y(y), num(num) {}
};

bool comp(Node a, Node b) {
  if (a.x < b.x) {
    return true;
  } else if (a.x == b.x) {
    return a.y > b.y;
  }
  return false;
}

bool comp2(Node a, Node b) {
  if (a.x > b.x) {
    return true;
  } else if (a.x == b.x) {
    return a.y > b.y;
  }
  return false;
}

void solve() {
  int n, h; cin >> n >> h;
  vector<Node> p;
  vector<Node> m;
  for (ll i = 0; i < n; ++i) {
    ll x, y, num = i;
    cin >> x >> y;
    if (y - x >= 0) {
      p.push_back({x, y, num});
    } else {
      m.push_back({x, y, num});
    }
  }

  sort(p.begin(), p.end(), comp);
  sort(m.begin(), m.end(), comp2);

  for (ll i = 0; i < p.size(); ++i) {
    if (h - p[i].x <= 0) {
      std::cout << "NIE\n";
      return;
    }
    h -= p[i].x;
    h += p[i].y;
  }

  for (int i = 0; i < m.size(); ++i) {
    if (h - m[i].x <= 0) {
      std::cout << "NIE\n";
      return;
    }
    h -= m[i].x;
    h += m[i].y;
  }

  cout << "TAK\n";

  // for (int i = 0; i < p.size(); ++i) {
  //   cout << p[i].num + 1 << " ";
  // }
  // for (int i = 0; i < m.size(); ++i) {
  //   cout << m[i].num + 1 << " ";
  // }
  // cout << "\n";
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