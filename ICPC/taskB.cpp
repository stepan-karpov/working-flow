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
using pii = pair<long long, long long>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string ALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

struct pt {
  long long x = 0, y = 0;
  pt() = default;
  pt(long long x, long long y): x(x), y(y) {}
};

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}

long long operator^(pt a, pt b) {
  return a.x * b.y - a.y * b.x;
}

bool intersect(pair<pt, pt> p1, pair<pt, pt> p2) {
  pt vec0 = p1.second - p1.first;
  pt vec1 = p2.first - p1.first;
  pt vec2 = p2.second - p1.first;
  pt cev0 = p2.second - p2.first;
  pt cev1 = p1.first - p2.first;
  pt cev2 = p1.second - p2.first;
  if (vec1 ^ vec0 == 0LL && vec2 ^ vec0 == 0LL) {
    long long l1 = p1.first.y;
    long long r1 = p1.second.y;
    long long l2 = p2.first.y;
    long long r2 = p2.second.y;
    return max(l1, l2) <= min(r1, r2);
  }
  return ((vec1 ^ vec0) * (vec2 ^ vec0) <= 0) && ((cev1 ^ cev0) * (cev2 ^ cev0) <= 0);
}

void solve() {
  long long n;
  cin >> n;
  vector<pair<pt, pt>> v;
  for (long long i = 0; i < n; ++i) {
    long long t, s, f;
    cin >> t >> s >> f;
    pt a(t, s);
    pt b(t + abs(f - s), f);
    v.push_back(pair<pt, pt>(a, b));
  }
  for (long long i = 0; i < n; ++i) {
    long long cnt = 0;
    // cerr << v[i].first.x << ' ' << v[i].first.y << ' ' << v[i].second.x << ' ' << v[i].second.y << '\n';
    for (long long j = 0; j < n; ++j) {
      if (j != i) {
        if (intersect(v[i], v[j])) cnt++;
      }
    }
    cout << cnt << ' ';
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