#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define sz(a) ((int)((a).size()))
#define mp(a, b) make_pair(a, b)
#define e "\n"
#define pb push_back
#define eb emplace_back
#define ft first
#define sc second
#define vi vector<int>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvl vector<vector<long long>>
#define unmap unordered_map
#define unset unordered_set
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
// #define max max<long long>
#define min min<int>
#define EPS 0.000000001
#define Time (double)clock() / CLOCKS_PER_SEC
#define filein(FILE) freopen(FILE, "r", stdin)
#define fileout(FILE) freopen(FILE, "w", stdout)
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng_ll(chrono::steady_clock::now().time_since_epoch().count());

template <typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> p) {
  out << '<' << p.first << " | " << p.second << '>';
  return out;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    out << vec[i];
    if (i + 1 != vec.size()) {
      out << " ";
    }
  }
  return out;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = 0; j < vec[i].size(); ++j) {
      out << vec[i][j];
      if (j + 1 != vec[j].size()) {
        out << " ";
      }
    }
    if (i != vec.size() - 1) out << e;
  }
  return out;
}

template <typename T>
void _dbg(const char* _s, T _h) {
  cerr << _s << " = " << _h << "\n";
}

template <typename T, typename... Ts>
void _dbg(const char* _s, T _h, Ts... _t) {
  for (int _b = 0; ((_b += *_s == '(') -= *_s == ')') != 0 || *_s != ',';)
    cerr << *_s++;
  cerr << " = " << _h << ",";
  _dbg(_s + 1, _t...);
}

#ifdef LOCAL
#define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...)
#endif

void fastios() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}

int binpow(int a, int n) {
  int result = 1;
  while (n) {
    if (n & 1) result *= a;
    a *= a;
    n >>= 1;
  }
  return result;
}
ll div_up(ll x, ll y) { return (x - 1) / y + 1; }

/*
const int ML = 240;
char memory[ML << 20];
size_t ptr_ = 0;

void* operator new(size_t how_much) {
    ptr_ += how_much;
    assert(ptr_ < ML * 1024 * 1024);
    return memory + ptr_ - how_much;
}

void operator delete(void*) { }
*/

#define int long long
int const INF = 2 * 1e9 * 1e9;
ll const LINF = 1e18;
const int MAXN = 4 * 100 * 1001;  // 1e5 + 0
// ll const CONST = 9223372036854775807;
long double const PI = 3.14159265358979323846;
// int const MAXN = 101;
const int SQRT = 350;
const int LOG = 21;
const int kMod = 1e9 + 7;

int gcd(int a, int b, int& x, int& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  int x1, y1;
  int d = gcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}
int n, m;
vi used;
vvi g;

void DFS(int v, int& hui, int cur = 0) {
  used[v] = true;
  cur++;
  hui = max(hui, cur);
  for (int to : g[v]) {
    if (used[to]) {
      continue;
    }
    cerr << v % n + 1 << " " << to % n + 1 << "\n";
    DFS(to, hui, cur);
  }
  --cur;
}



void solve() {
  cin >> n >> m;

  used.resize(n + n + 2);

  vi is_bad(n);
  int total_good = 0;
  for (auto& i : is_bad) {
    cin >> i;
    total_good += (i == 1);
    --i;
  }
  vvi g1(n);
  for (int from, to, i = 0; i < m; ++i) {
    cin >> from >> to;
    --from;
    --to;
    g1[from].eb(to);
    g1[to].eb(from);
  }
  for (int i = 0; i < n; ++i) {
    if (sz(g1[i]) > 2) {
      is_bad[i] = false;
    }
  }

  vi palki;
  palki.push_back(0);
  palki.push_back(0);
  int xrest = 0;
  for (int i = 0; i < n; ++i) {
    if (g1[i].size() == 1 && is_bad[i]) {
      int val = 1;
      int prev = i;
      int v = g1[i][0];
      while(g1[v].size() == 2 && is_bad[v]) {
        if (g1[v][0] != prev) {
          prev = v;
          v = g1[v][0];
        } else {
          prev = v;
          v = g1[v][1];
        }
        val += 1;
      }
      if (g1[v].size() == 1 && is_bad[v]) {
        val += 1;
      }
      palki.push_back(val);
    }
  }
  sort(palki.rbegin(), palki.rend());
//  for (int i : palki) cerr << i << '_';
  int my_sizik = palki.size();
  for (int i = my_sizik; i >= 2; --i) {
    n -= palki[i];
  }
  cout << n << '\n';
//  g.resize(n + n + 2);
//  for (int from = 0; from < sz(g1); ++from) {
//    if (!is_bad[from]) {
//      g[from].eb(from + n);
//      g[from + n].eb(from);
//    }
//    for (int to : g1[from]) {
//      g[from].eb(to);
//      g[to].eb(from);
//      if (!is_bad[to]) {
//        g[from].eb(to + n);
//        g[to + n].eb(from);
//      }
//      if (!is_bad[from]) {
//        g[from + n].eb(to);
//        g[to].eb(from + n);
//        if (!is_bad[to]) {
//          g[from + n].eb(to + n);
//          g[to + n].eb(from + n);
//        }
//      }
//    }
//  }
//
//
  
}

signed main() {
  fastios();
  solve();
  return 0;
}