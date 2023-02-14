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

void output(vll& a) {
  for (int i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << "\n";
}

ll findAnswer(vll& cur_prefix, ll m) {
  if (cur_prefix.size() < m) {
    return INF;
  }
  ll n = cur_prefix.size();
  ll answer = INF;
  for (int i = 0; i < (1 << n); ++i) {
    vll cur_subset;
    for (int j = n - 1; j >= 0; --j) {
      bool t = (i >> j) & 1;
      if (t) {
        cur_subset.push_back(cur_prefix[j]);
      }
    }
    if (cur_subset.size() != m) {
      continue;
    }
    ll current_answer = 0;
    for (int j = 0; j < n; ++j) {
      ll best = 1e9;
      for (int k = 0; k < cur_subset.size(); ++k) {
        best = min(best, abs(cur_prefix[j] - cur_subset[k]));
      }
      current_answer += best;
    }
    answer = min(answer, current_answer);
  }
  return answer;
}

void solve() {
  ll n, m; cin >> n >> m;
  vll a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // vll temp = {1, 2};
  // findAnswer(temp, 1);

  vvll dp(m + 1, vll(n + 1, INF));

  for (int i = 1; i <= m; ++i) {
    for (int r = 1; r <= n; ++r) {
      vll cur_prefix;
      for (int k = 1; k <= r; ++k) {
        cur_prefix.push_back(a[k]);
      }
      dp[i][r] = findAnswer(cur_prefix, i);
    }
  }

  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (dp[i][j] == INF) {
        std::cout << "i  " << " ";
      } else {
        std::cout << dp[i][j] << " ";
        if (dp[i][j] < 10) {
          std::cout << " ";
        }
        if (dp[i][j] < 100) {
          std::cout << " ";
        }
      }
    }
    std::cout << "\n";
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