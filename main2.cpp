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

bool possible(ll n, vll &a) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        a[0] = 0;
        return 1;
    } else if (n == 2) {
        a[0] = 1;
        a[1] = 0;
        return 1;
    }
    ll curV = 0;

    while (curV * curV < (n - 1)) {
        ++curV;
    }

    ll start = curV * curV - n + 1;

    if (!(0 <= start && start < n))
        return 0;

    for (ll i = start; i < n; ++i) {
        a[i] = n - (i - start) - 1;
    }
    return possible(start, a);

}

void solve() {
    ll n; cin >> n;
    vll a(n, 0);

    if (!possible(n, a)) {
        cout << -1 << endl;
        return;
    } else {
        for (ll i = 0; i < n; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
 
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    cin >> t;
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