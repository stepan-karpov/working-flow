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

bool possible(vll &a, ll d, ld x) {

    ll n = a.size();
    vector<ld> b(n);

    for (ll i = 0; i < n; ++i) {
        b[i] = ld(a[i]) - x;
    }

    vector<ld> s(n);

    s[0] = b[0];

    for (ll i = 1; i < n; ++i) {
        s[i] = s[i - 1] + b[i];
    }

    ld max_s = s[d - 1];
    ld min_s = 0;

    for (ll r = d; r < n; ++r) {
        min_s = min(min_s, s[r - d]);
        max_s = max(max_s, s[r] - min_s);
    }

    return (max_s >= 0);

}

ld bin_search(vll &a, ll d) {

    ld l = 0;
    ld r = 1e8;

    for (ll i = 0; i < 100; ++i) {

        ld m = (l + r) / 2;

        if (possible(a, d, m)) {
            l = m;
        } else {
            r = m;
        }

    }

    return l;

}

pll solve(vll a, ll d) {
    ll n = a.size();
    ld x = bin_search(a, d);
    // cout << x << endl;

    vector<ld> b(n);

    for (ll i = 0; i < n; ++i) {
        b[i] = ld(a[i]) - x;
    }

    vector<ld> s(n);

    s[0] = b[0];

    for (ll i = 1; i < n; ++i) {
        s[i] = s[i - 1] + b[i];
    }

    ll ans_l = 0;
    ll ans_r = d - 1;

    ld max_s = s[d - 1];

    ll best_l = -1;
    ld min_s = 0;

    for (ll r = d; r < n; ++r) {
        if (s[r - d] < min_s) {
            min_s = min(min_s, s[r - d]);
            best_l = r - d;
        }
        if (s[r] - min_s > max_s) {
            max_s = max(max_s, s[r] - min_s);
            ans_l = best_l + 1;
            ans_r = r;
        }
    }

    return {ans_l, ans_r};

}

bool check(vll a, pll best, ll d) {

    ll n = a.size();

    ll ans_l = best.first;
    ll ans_r = best.second;

    if (ans_r - ans_l + 1 < d) {
        return 0;
    } 

    ll best_len = ans_r - ans_l + 1;
    ll best_sum = 0;

    for (ll i = ans_l; i <= ans_r; ++i) {
        best_sum += a[i];
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < i; ++j) {
            if (i - j + 1 < d)
                continue;

            ll cur_s = 0;
            ll cur_len = i - j + 1;

            for (ll k = j; k <= i; ++k) {
                cur_s += a[k];
            }

            if (cur_s * best_len > best_sum * cur_len)
                return 0;

        }
    }

    return 1;

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1000;
    // cin >> t;
    // cout << fixed << setprecision(10);
    
    ll n = 5;
    ll d = 3;
    vll a(n);

    while (t--) {
        for (ll i = 0; i < n; ++i) {
            a[i] = rand() % 20;
        }
        d = rand() % n + 1;

        pll ans = solve(a, d);

        if (!check(a, ans, d)) {
            cout << "WA!!" << endl;
            cout << n << " " << d << endl;
            for (ll i = 0; i < n; ++i) {
                cout << a[i] << " ";
            }
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
        } else {
            // cout << "OK" << endl;
        }

        // cout << solve() << endl;
        // if (solve())
        //    cout << "Yes" << endl;
        // else
        //    cout << "No" << endl;
    }

    return 0;
}