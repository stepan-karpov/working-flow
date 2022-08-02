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


void solve() {
    string t; cin >> t;
    ll n; cin >> n;
    vector<string> a(n);

    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vll dp(t.size() + 100, INF);
    vector<string> addedStr(t.size() + 100);
    vll pnt(t.size() + 100, -1);

    for (ll i = 0; i < t.size(); ++i) {
        for (ll j = 0; j < n; ++j) {
            ll start = i - a[j].size() + 1;
            if (start < 0) {
                continue;
            }
            string curS = t.substr(start, a[j].size());

            if (curS != a[j])
                continue;

            if (start == 0) {
                dp[i] = 1;
                addedStr[i] = curS;
                pnt[i] = -1;
                continue;
            }

            for (ll k = start - 1; k < i; ++k) {
                if (dp[k] + 1 < dp[i]) {
                    dp[i] = dp[k] + 1;
                    addedStr[i] = curS;
                    pnt[i] = k;
                }
            }

        }
    }

    if (dp[t.size() - 1] == INF) {
        cout << -1 << endl;
        return;
    }

    ll curPnt = t.size() - 1;

    vector<pll> ans;

    while (curPnt != -1) {

        for (ll i = 0; i < n; ++i) {
            if (addedStr[curPnt] == a[i]) {
                ans.push_back({i + 1, curPnt - a[i].size() + 2});
                break;
            }
        }

        curPnt = pnt[curPnt];

    }

    cout << dp[t.size() - 1] << endl;

    for (ll i = ans.size() - 1; i >= 0; --i) {
        cout << ans[i].first << " " << ans[i].second << endl;
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