
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>
#include <chrono>
#include <random>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <functional>
#include <sstream>
#define LOCAL
#define DLOCAL
#define sz(a) ((int)((a).size()))
#define get(_type, _x) \
    _type _x; \
    cin >> _x
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
#define max max<int>
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

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> p) {
    out << '<' << p.first << " | " << p.second << '>';
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i + 1 != vec.size()) {
            out << " ";
        }
    }
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            out << vec[i][j];
            if (j + 1 != vec[j].size()) {
                out << " ";
            }
        }
        if (i != vec.size() - 1)
            out << e;
    }
    return out;
}


template<typename T>
void _dbg(const char* _s, T _h) { cerr << _s << " = " << _h << "\n"; }

template<typename T, typename... Ts>
void _dbg(const char* _s, T _h, Ts... _t) {
    for (int _b = 0; ((_b += *_s == '(') -= *_s == ')') != 0 || *_s != ',';)cerr << *_s++;
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

#ifdef dsdsDDSDSDLOCAL
    filein("inputf.in");
    fileout("outputf.out");
#endif

}


int binpow(int a, int n) {
    int result = 1;
    while (n) {
        if (n & 1)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}
ll div_up(ll x, ll y) {
    return (x - 1) / y + 1;
}

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



#define int int64_t
int const INF = 2 * 1e9 * 1e9;
ll const LINF = 1e18;
const int MAXN = 4 * 100 * 1001; // 1e5 + 0
//ll const CONST = 9223372036854775807;
long double const PI = 3.14159265358979323846;
//int const MAXN = 101;
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


struct edge {
  int to, w;
  edge() = default;
  edge(int h, int s) {
    to = h; w = s;
  }
};

vector<vector<edge>> g;

struct printer {
  int v, time, comp_in_minute;
  printer() = default;
  printer(int i1, int i2, int i3) {
    v = i1; time = i2;
    comp_in_minute = i3;
  }
};

void Solve() {
  int n, m, k; cin >> n >> m >> k;
  int start = 0;
  g.resize(n);
  for (int u, v, c, i = 0; i < m; ++i) {
    cin >> u >> v >> c;
    --u; --v;
    g[u].eb(v, c);
    g[v].eb(u, c);
  }
  vector<int> cost(n, INF);
  set<pair<int, int>> q;
  cost[start] = 0;
  q.emplace(0, start);

  while (!q.empty()) {
      int v = q.begin() -> sc;
      q.erase(q.begin());
      for (auto & [to, w] : g[v]) {
          if (cost[to] > cost[v] + w) {
              q.erase({cost[to], to});
              cost[to] = cost[v] + w;
              q.emplace(cost[to], to);
          }
      }
  }

  int printers; cin >> printers;
  vector<printer> p(printers);
  for (auto& [v, t, c] : p) {
    cin >> v >> t >> c;
    --v;
  }

  int v; cin >> v;
  int l = 0, r = 2e18;
  while (r - l > 1) {
    ull mid = (l + r) / 2;
    dbg(mid);
    vector<ull> constructed;
    for (auto& [v, t, c] : p) {
      ull tiume = t + 2 * cost[v];
      if (mid <= tiume) {constructed.eb(0); continue;}
      ull time_to_do = mid - time_to_do;
      constructed.eb(time_to_do / c);
    }
  
    sort(all(constructed));
    ull ans = 0;
    for (int i = printers - k; i < printers; ++i) {
      ans += constructed[i];
    }
    dbg(ans);
    if (ans >= v) {
      r = mid;
    } else {
      l = mid;
    }
  }
  auto do_ans = [&](ull time) -> bool {
    vector<ull> constructed;
    for (auto& [v, t, c] : p) {
      ull tiume = t + 2 * cost[v];
      if (time <= tiume) {constructed.eb(0); continue;}
      ull time_to_do = time - tiume;
      constructed.eb(time_to_do / c);
    }
  
    sort(all(constructed));
    ull ans = 0;
    for (int i = printers - k; i < printers; ++i) {
      ans += constructed[i];
    }
    return ans >= v;
  };
  cout << l << e;

  --l; --l; --l;
  l = max(0, l);
  while (!do_ans(l)) {
    ++l;
  }
  cout << l << e;
  cout << do_ans(186828523658764908) << e << do_ans(109474112660635110);
}


signed main() {
    fastios();
    Solve();
    return 0;
}