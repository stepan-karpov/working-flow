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

void make_set (int v, vll& parent, vll& rank) {
	parent[v] = v;
	rank[v] = 0;
}
 
int find_set (int v, vll& parent, vll& rank) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v], parent, rank);
}
 
void union_sets (int a, int b, vll& parent, vll& rank) {
	a = find_set(a, parent, rank);
	b = find_set(b, parent, rank);
	if (a != b) {
		if (rank[a] < rank[b])
			swap (a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			++rank[a];
	}
}

void solve() {
  ll n; cin >> n;
  vvll E(n + 1);
  vector<pair<ll, pll>> edges;
  vll comp(n + 1);
  vll rank(n + 1);

  for (int i = 0; i <= n; ++i) {
    make_set(i, comp, rank);
  }

  ll added = 0;
  ll sum = 0;

  for (ll i = 0; i < n; ++i) {
    for (ll j = i + 1; j <= n; ++j) {
      ll x; cin >> x;
      edges.push_back({x, {i, j}});
    }
  }
  sort(edges.begin(), edges.end());
  auto it = edges.begin();
  while (added < n) {
    ll u = it->second.first;
    ll v = it->second.second;
    ll w = it->first;
    ++it;
    if (find_set(u, comp, rank) != find_set(v, comp, rank)) {
      union_sets(u, v, comp, rank);
      sum += w;
      ++added;
    }
  }

  

  cout << sum << "\n";

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