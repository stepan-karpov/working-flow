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

// v2 = rand() % 100 + 1;  --- v2 in the range 1 to 100

struct node {
    ll curS = 0;
};

struct seg_tree {

    ll size = 1;
    vector<node> tree;

    node ZERO;

    void init(ll n) {
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, ZERO);
    }

    void add(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        if (l <= lx && rx <= r) {
            tree[x].curS += v;
            return;
        }

        ll m = (lx + rx) / 2;

        add(l, r, v, 2 * x + 1, lx, m);
        add(l, r, v, 2 * x + 2, m, rx);
    }

    void add(ll l, ll r, ll v) {
        add(l, r, v, 0, 0, size);
    }

    ll get_value(ll p, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            return tree[x].curS;
        }

        ll m = (rx + lx) / 2;
        
        if (p < m) {
            return tree[x].curS + get_value(p, 2 * x + 1, lx, m);
        }

        return tree[x].curS + get_value(p, 2 * x + 2, m, rx);

    }

    ll get_value(ll p) {
        return get_value(p, 0, 0, size);
    }

};

void solve() {
    ll n,  m; cin >> n >> m;

    seg_tree a;
    a.init(n);

    for (ll i = 0; i < m; ++i) {
        ll cmd; cin >> cmd;
        if (cmd == 1) {
            ll l, r, v; cin >> l >> r >> v;
            a.add(l, r, v);
        } else {
            ll p; cin >> p;
            cout << a.get_value(p) << endl;            
        }
    }

}

int main(){
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