#include <bits/stdc++.h>
using namespace std;

const int kBigmac = 100;
const int kInf = 1e9;
const int kSmall = 100000;

void Unsync() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);
}

void PrintAns(const vector<int>& path) {
  cout << "YES\n";
  // cout << path.size() << "\n";
  // for (int vertice : path) {
  //   cout << vertice + 1 << " ";
  // }
}

void Solve() {
  int vert;
  cin >> vert;
  int adj[kBigmac][kBigmac];
  vector<vector<int>> edges;
  vector<int> ans(vert);
  vector<int> prev(vert, -1);
  vector<int> path;
  ans[0] = 0;
  for (int i = 0; i < vert; ++i) {
    for (int j = 0; j < vert; ++j) {
      cin >> adj[i][j];
      if (adj[i][j] != kSmall) {
        edges.push_back({i, j, adj[i][j]});
      }
    }
  }
  int head = -1;
  for (int i = 0; i < vert; ++i) {
    head = -1;
    for (vector<int> ed : edges) {
      int vu = ed[0];
      int uv = ed[1];
      int ro = ed[2];
      if (ans[vu] != kInf && ans[vu] + ro < ans[uv]) {
        ans[uv] = max(-kInf, ans[vu] + ro);
        prev[uv] = vu;
        head = uv;
      }
    }
  }
  if (head == -1) {
    cout << "NO\n";
    return;
  }
  int tail = head;
  for (int i = 0; i < vert; ++i) {
    tail = prev[tail];
  }
  for (int cur = tail;; cur = prev[cur]) {
    path.push_back(cur);
    if (cur == tail && path.size() > 1) {
      break;
    }
  }
  reverse(path.begin(), path.end());
  PrintAns(path);
}

int main() {
  Unsync();
  Solve();
}