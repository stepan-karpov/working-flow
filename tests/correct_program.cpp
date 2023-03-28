#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define int long long
using namespace std;
using pii = pair<int, int>;

signed main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  vector<pii> b(m);
  for (int &i : a) cin >> i;
  for (int i = 0; i < m; ++i) {
    cin >> b[i].first;
    b[i].second = i;
  }
  sort(b.begin(), b.end());
  queue<int> empt;
  vector<int> ans(m);
  for (int i = 0; i < m; ++i) {
    if (empt.size() == 0) {
      int first = 1e18;
      for (int j = 0; j < n; ++j) {
        if (a[j] != -1) {
          if (first > ((b[i].first + a[j] - 1) / a[j]) * a[j]) {
            first = ((b[i].first + a[j] - 1) / a[j]) * a[j];
          }
        }
      }
      for (int j = 0; j < n; ++j) {
        if (a[j] != -1) {
          if (((b[i].first + a[j] - 1) / a[j]) * a[j] == first) {
            empt.push(j);
            a[j] = -1;
          }
        }
      } 
      ans[b[i].second] = first;
      empt.pop();
    } else {
      ans[b[i].second] = b[i].first;
      empt.pop();
    }
  }
  for (int i : ans) cout << i << ' ';
  cout << '\n';
  return 0;
} 