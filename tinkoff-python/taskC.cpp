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

void Solve() {
  int n; cin >> n;
  string s; cin >> s;

  vll pos(4, -1);

  for (int i = 0; i < s.size(); ++i) {
    if (pos[s[i] - 'a'] == -1) {
      pos[s[i] - 'a'] = i;
    }
  }

  if (pos[0] == -1 || pos[1] == -1 || pos[2] == -1 || pos[3] == -1) {
    cout << -1 << "\n";
    return;
  }

  int start = max({pos[0], pos[1], pos[2], pos[3]});
  int ans = start + 1;

  vll cnt(4);
  int l = 0;


  for (int i = 0; i <= start; ++i) {
    ++cnt[s[i] - 'a'];
  }

  while (cnt[s[l] - 'a'] > 1) {
    --cnt[s[l] - 'a'];
    ++l;
  }

  ans = min(ans, start - l + 1);

  for (int r = start + 1; r < s.size(); ++r) {
    ++cnt[s[r] - 'a'];
    while (cnt[s[l] - 'a'] > 1) {
      --cnt[s[l] - 'a'];
      ++l;
    }
    ans = min(ans, r - l + 1);
  }

  std::cout << ans << "\n";

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