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

    int compress(vector<char>& chars) {
        if (chars.size() == 1) { return 1; }
        int p = 0;
        int last = 0;
        int answer = 0;

        for (int i = 1; i < chars.size(); ++i) {
            if (chars[i] != chars[i - 1]) {
                int current_length = i - last;
                ++answer;
                chars[p] = chars[i - 1]; ++p;
                if (current_length != 1) {
                  for (auto c : std::to_string(current_length)) {
                      ++answer;
                      chars[p] = c; ++p;
                  }
                }
                last = i;
            }
        }
        int i = chars.size();

        int current_length = i - last;
        ++answer;
        chars[p] = chars[i - 1]; ++p;
        if (current_length != 1) {
          for (auto c : std::to_string(current_length)) {
              ++answer;
              chars[p] = c; ++p;
          }
        }
        chars.resize(answer);
        return answer;
    }

void solve() {
  vector<char> temp = {'a','b','b','b','b','b','b','b','b','b','b','b','b'};
  compress(temp);

  for (int i = 0; i < temp.size(); ++i) {
    cout << temp[i];
  }
  cout << "\n";
  
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