#include <bits/stdc++.h>
using namespace std;

using ll = int;
using vll = vector<ll>;
using vvll = vector<vll>;

const ll MOD = 998244353;


ll bin_search(ll n, ll k) {

    ll l = 0;
    ll r = 1e4;

    while (r - l > 1) {
        ll m = (l + r) / 2;

        ll curV = (m + 1) * (k + m);
        if (curV >= 2 * n) {
            r = m;
        } else {
            l = m;
        }

    }

    return r;

}

void solve() {
    ll n, k; cin >> n >> k;
    ll x = bin_search(n, k);
    cout << x << endl;
    vvll a(x + 100, vll(n + 10, 0));
    a[0][0] = 1;
    vll ans(n + 10, 0);

    ll cur_s = k;
    ll cur_add = k;
    for (ll i = 1; i <= x; ++i) {
        for (ll j = cur_s; j <= n; ++j) {
            a[i][j] = (a[i][j - cur_add] + a[i - 1][j - cur_add]) % MOD;
            ans[j] = (ans[j] + a[i][j]) % MOD;
        }
        ++cur_add;
        cur_s += cur_add;
    }

    // for (ll i = 0; i <= x; ++i) {
    //     cout << i << ": ";
    //     for (ll j = 0; j <= n; ++j) {
    //         cout << a[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (ll i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;






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