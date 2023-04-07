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
  int w1, w2, h1, h2;
};

void Solve() {
  ll n; cin >> n;
  vector<Node> a(n);

  for (int i = 0; i < n; ++i) {
    cin >> a[i].w1 >> a[i].w2 >> a[i].h1 >> a[i].h2;
  }

  int mw1 = a[0].w1;
  int mw2 = a[0].w2;
  int mh1 = a[0].h1;
  int mh2 = a[0].h2;

  for (int i = 0; i < n; ++i) {
    mw1 = min(mw1, a[i].w1);
    mw2 = max(mw2, a[i].w2);
    mh1 = min(mh1, a[i].h1);
    mh2 = max(mh2, a[i].h2);
  }

  for (int i = 0; i < n; ++i) {
    if (a[i].w1 == mw1 && a[i].w2 == mw2 &&
        a[i].h1 == mh1 && a[i].h2 == mh2) {
      cout << "TAK\n";
      return;
    }
  }

  cout << "NIE\n";


}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll t = 1;
  cin >> t;
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