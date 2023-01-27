#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;

ll binarySearch(vll &a, ll x) {
    //   l:   <= x     r: > x
    // ---------------|-------
    // ..  ..  ..  ..   ..  ..
    // returns the first element that's less or equal than x
    ll l = -1;
    ll r = a.size();

    while (r > l + 1) {
        ll m = (r + l) / 2;
        if (a[m] <= x)
            l = m;
        else
            r = m;
    }

    cout << l << " " << r << endl;

    return l;
    // l contains the element that's less or equal than x (or -1)
    // r contains the element that's more than x (or n)
}

ll binarySearch2(vll &a, ll x) {
    
    //   l:   < x      r: >= x
    // ---------------|-------
    // ..  ..  ..  ..   ..  ..
    // returns the first element that's more or equal than x
    ll l = -1;
    ll r = a.size();

    while (r > l + 1) {
        ll m = (r + l) / 2;
        if (a[m] < x)
            l = m;
        else
            r = m;
    }

    cout << l << " " << r << endl;

    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    // cin >> t;
    // cout << fixed << setprecision(10);

    ll n; cin >> n;
    vll a(n);
    for (ll i = 0; i < n; ++i) cin >> a[i];

    while (1) {
        ll x; cin >> x;
        binarySearch2(a, x);
    }

    return 0;
}