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

ll Read() {
  string s; cin >> s;
  ll p = 0;
  ll ans = 0;
  for (int i = s.size() - 1; i >= 0; --i) {
    if (s[i] == '1') {
      ans += (1 << p);
    }
    ++p;
  }
  return ans;
}

struct Node {
  ll d, cure, new_sympt;
  Node() = default;
  Node(ll d, ll cure, ll new_sympt)
    : d(d), cure(cure), new_sympt(new_sympt) {}
};


void solve() {
  ll n, m; cin >> n >> m;
  ll start = Read();
  vector<Node> treats(m);

  for (int i = 0; i < m; ++i) {
    ll a, b, c; cin >> a;
    b = Read();
    c = Read();
    treats[i] = Node(a, b, c);
  }

  vll dist((1 << n) + 100, INF);

  set<pll> q;
  q.insert({0, start});

  while (!q.empty()) {
    ll cur_d = q.begin()->first;
    ll cur_v = q.begin()->second;
    q.erase(q.begin());
    if (dist[cur_v] != INF) { continue; }
    dist[cur_v] = cur_d;

    for (int i = 0; i < treats.size(); ++i) {
      ll c1 = cur_v;
      ll c2 = ~treats[i].cure;
      ll c3 = treats[i].new_sympt;
      ll to = (c1 & c2) | c3;
      if (dist[to] != INF) { continue; }
      q.insert({cur_d + treats[i].d, to});
    }
  }

  if (dist[0] == INF) {
    dist[0] = -1;
  }
  cout << dist[0] << "\n";

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  cin >> t;
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