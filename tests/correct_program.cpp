#include <bits/stdc++.h>
using namespace std;

const int kSz = 1e3;
const int kInf = 1e9 + 2;
const int kTwo = 2;
const int kO = 1;
const int kZ = 0;

void Unsync() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);
}

struct SegT {
  long long ts[3][kSz];
  long long arr[kSz];
  long long now;
  unordered_map<long long, long long> map;

  SegT() {
    memset(ts, 0, sizeof(ts));
    memset(arr, 0, sizeof(arr));
    now = (kO << kO);
  }

  long long DoIth(long long v, long long l, long long r, long long k) {
    if (r - l == kO) {
      return l;
    }
    if (ts[kZ][ts[kO][v]] < k) {
      return DoIth(ts[kTwo][v], (l + r) / kTwo, r, k - ts[kZ][ts[kO][v]]);
    }
    return DoIth(ts[kO][v], l, (l + r) / kTwo, k);
  }

  long long Ith(long long r, long long k) {
    long long one = 1;
    return DoIth(one, kZ, r, k);
  }

  void DoUp(long long v, long long l, long long r, long long idx,
            long long val) {
    if (r - l == kO) {
      long long sq = sqrt(arr[v]);
      arr[v] += val * (kTwo * sq + val);
      if (arr[v] == kZ) {
        ts[kZ][v] = kZ;
      } else {
        ts[kZ][v] = kO;
      }
      map[l] = sqrt(arr[v]);
      return;
    }
    if (ts[kO][v] == kZ) {
      ts[kO][v] = now;
      now += kO;
      ts[kTwo][v] = now;
      now += kO;
    }
    if (idx >= (l + r) / kTwo) {
      DoUp(ts[kTwo][v], (l + r) / kTwo, r, idx, val);
    } else {
      DoUp(ts[kO][v], l, (l + r) / kTwo, idx, val);
    }
    ts[kZ][v] = ts[kZ][ts[kO][v]] + ts[kZ][ts[kTwo][v]];
    arr[v] = arr[ts[kO][v]] + arr[ts[kTwo][v]];
  }

  void Up(long long r, long long idx, long long val) {
    long long one = 1;
    DoUp(one, kZ, r, idx, val);
  }

  pair<long long, long long> Get(long long idx) {
    pair<long long, long long> p(map[idx] / kTwo, map[idx] % kTwo);
    return p;
  }

  void ErRight(long long i) {
    long long r = Ith(kInf, i + kO);
    Up(kInf, Ith(kInf, i), map[r]);
    Up(kInf, r, -map[r]);
  }

  void ErLeft(long long i) {
    long long idx = Ith(kInf, i);
    long long l = Ith(kInf, i - kO);
    long long r = Ith(kInf, i + kO);
    Up(kInf, l, Get(idx).first);
    Up(kInf, r, (Get(idx).first + Get(idx).second));
    long long fir = map[idx];
    Up(kInf, idx, -fir);
    long long sec = map[r];
    Up(kInf, r, -sec);
    Up(kInf, r - (fir / kTwo) - (fir % kTwo), sec);
  }

  void ErMid(long long i) {
    long long idx = Ith(kInf, i);
    long long l = Ith(kInf, i - kO);
    Up(kInf, l, map[idx]);
    Up(kInf, idx, -map[idx]);
  }

  void Er(long long i) {
    if (i <= kO) {
      ErRight(i);
    } else {
      if (i < ts[kZ][kO]) {
        ErLeft(i);
      } else {
        ErMid(i);
      }
    }
  }

  void De(long long k) {
    long long idx = Ith(kInf, k);
    Up(kInf, idx + Get(idx).first, Get(idx).second + Get(idx).first);
    Up(kInf, idx, -Get(idx).second - Get(idx).first);
  }
};

void Solve() {
  long long n, nup;
  cin >> n >> nup;
  vector<long long> vec(n);
  SegT st;
  long long reduced = kZ;
  for (long long i = kZ; i < n; ++i) {
    cin >> vec[i];
  }
  for (long long i = kZ; i < n; ++i) {
    long long a = vec[i];
    st.Up(kInf, reduced, a);
    reduced += a;
  }
  cout << st.arr[kO] << "\n";
  long long q;
  cin >> q;
  for (long long i = kZ; i < q; ++i) {
    long long t, k;
    cin >> t >> k;
    if (t == kO) {
      st.Er(k);
    } else {
      st.De(k);
    }
    cout << st.arr[kO] << "\n";
  }
}

int main() {
  Unsync();
  Solve();
}