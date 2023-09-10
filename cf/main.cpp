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
const string kALPH = "abcdefghijklmnopqrstuvwxyz";

ll find(string& str, char s) {
  for (long long i = 0; i < str.size(); ++i) {
    if (str[i] == s) {
      return i;
    }
  }
  return str.size();
}

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

// how many letter should we change
// to make a string balanced?
// k - number of letters we use
ll use_only_i_letters(string& s, ll k) {
  ll n = s.size();
  ll t = n / k; // how many time we should use each letter

  if (t * k != n) {
    return INF;
  }

  vector<ll> coords(kALPH.size(), 0);

  for (long long i = 0; i < n; ++i) {
    ++coords[s[i] - 97];
  }

  vector<pair<ll, ll>> usage;

  for (long long i = 0; i < kALPH.size(); ++i) {
    usage.push_back({coords[i], i});
  }

  sort(usage.begin(), usage.end());

  ll ans = INF;

  for (long long i = 0; i < kALPH.size(); ++i) {
    ll cur_ans = 0;
    for (long long j = i; j < i + k; ++j) {
      cur_ans += abs(t - usage[j].first);
    }
    ans = min(ans, cur_ans);
  }

  return ans / 2;
}

char find_cand(string& new_alph, vll& coords, ll t) {
  for (long long i = 0; i < kALPH.size(); ++i) {
    if (find(new_alph, kALPH[i]) == new_alph.size()) {
      continue;
    }

    if (coords[i] > t) {
      --coords[i];
      return kALPH[i];
    }

  }
  return kALPH[0];
}

void Solve() {
  ll n;
  cin >> n;
  string s;
  cin >> s;


  ll ans_t = INF;
  ll ind = 1;
  for (long long i = 1; i <= kALPH.size(); ++i) {
    ll cur_ans = use_only_i_letters(s, i);
    if (cur_ans < ans_t) {
      ans_t = cur_ans;
      ind = i;
    }
    // cout << i << ": " << cur_ans << '\n';
  }


  ll k = ind;
  ll t = n / k; // how many time we should use each letter

  vector<ll> coords(kALPH.size(), 0);

  for (long long i = 0; i < n; ++i) {
    ++coords[s[i] - 97];
  }

  vector<pair<ll, ll>> usage;

  for (long long i = 0; i < kALPH.size(); ++i) {
    usage.push_back({coords[i], i});
  }

  sort(usage.begin(), usage.end());

  ll ans = INF;
  ll to_start = -1;

  for (long long i = 0; i < kALPH.size(); ++i) {
    ll cur_ans = 0;
    for (long long j = i; j < i + k; ++j) {
      cur_ans += abs(t - usage[j].first);
    }
    if (ans < cur_ans) {
      ans = cur_ans;
      to_start = i;
    }
  }

  cout << to_start << '\n';
  cout << '\n';

  string new_alph = "";
  cout << to_start << '\n';
  cout << '\n';
  cout << '\n';
  cout << k << '\n';
  cout << '\n';
  cout << '\n';

  for (long long i = to_start; i < to_start + k; ++i) {
    new_alph += kALPH[usage[i].second];
  }

  vll new_usage(30, 0);

  for (long long i = 0; i < n; ++i) {
    if (find(new_alph, s[i]) != new_alph.size()) { // s[i] in new_alph
      ll used = new_usage[kALPH.find(s[i])];
      if (used < t) {
        ++new_usage[kALPH.find(s[i])];
      } else {

        char new_value = find_cand(new_alph, coords, t);
        ++new_usage[kALPH.find(new_value)];
        s[i] = new_value;

      }
    } else {
      char new_value = find_cand(new_alph, coords, t);
      ++new_usage[kALPH.find(new_value)];
      s[i] = new_value;
    }
  }



  cout << s << '\n';
}

long long main() {
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