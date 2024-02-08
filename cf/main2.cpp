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
using pii = pair<ll, ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;

const ll INF = 1e16;
const ld EPS = 1e-8;
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

ll find(string& str, char s) {
  for (ll i = 0; i < str.size(); ++i) {
    if (str[i] == s) {
      return i;
    }
  }
  return str.size();
}

// k is number of string we can use
string get_string(string s, ll k, vector<pair<ll, ll>>& usage) {
  ll n = s.size();
  ll t = n / k; // how many times we should used single letter


  ll ans = INF;
  ll to_start = -1;

  for (ll i = 0; i <= kALPH.size() - k; ++i) {
    ll cur_ans = 0;
    for (ll j = i; j < i + k; ++j) {
      cur_ans += abs(t - usage[j].first);
    }
    if (cur_ans <= ans) {
      ans = cur_ans;
      to_start = i;
    }
  }

  string new_alph = "";
  vll rest(30, 0);

  for (ll i = to_start; i < to_start + k; ++i) {
    rest[usage[i].second] = t;
    new_alph += kALPH[usage[i].second];
  }

  vll fixed(n, 0);

  for (ll i = 0; i < n; ++i) {
    ll pos = find(new_alph, s[i]);
    if (pos != new_alph.size()) {
      ll pos_in_alph = kALPH.find(new_alph[pos]);
      if (rest[pos_in_alph] > 0) {
        --rest[pos_in_alph];
        fixed[i] = 1;
      }
    }
  }

  for (ll i = 0; i < n; ++i) {
    if (fixed[i] == 0) {
      ll v = 0;
      for (ll j = 0; j < 30; ++j) {
        if (rest[j] != 0) {
          v = j;
          break;
        }
      }
      s[i] = kALPH[v];
      --rest[v];
    }
  }

  return s;

}

void Solve() {
  ll n;
  cin >> n;
  string s;
  cin >> s;
  vll coords(kALPH.size(), 0);
  for (ll i = 0; i < s.size(); ++i) {
    ++coords[kALPH.find(s[i])];
  }
  vector<pair<ll, ll>> used;
  for (ll i = 0; i < kALPH.size(); ++i) {
    used.push_back({coords[i], i});
  }

  sort(used.begin(), used.end());

  string ans = "";
  ll cur_d = INF;

  for (ll i = 1; i <= kALPH.size(); ++i) {
    if (n % i != 0) {
      continue;
    }
    string new_s = get_string(s, i, used);
    
    ll cnt = 0;
    for (ll i = 0; i < n; ++i ) {
      if (s[i] != new_s[i]) {
        ++cnt;
      }
    }
    if (cnt < cur_d) {
      ans = new_s;
      cur_d = cnt;
    }
  }

  cout << cur_d << '\n';
  cout << ans << '\n';

}

ll main() {
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