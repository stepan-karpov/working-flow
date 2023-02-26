
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

#ifdef LOCAL
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



#define int long long
int const INF = 2 * 1e9;
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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> days(m);
    unmap<int, vector<int>> um;
    
}

signed main() {
    fastios();
    solve();
    return 0;
}