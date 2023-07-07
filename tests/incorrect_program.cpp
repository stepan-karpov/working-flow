#include <bits/stdc++.h>
#define int long long
#define re(a, b, c, d) for (auto a = b; a <= c; a += d)
#define de(a, b, c, d) for (auto a = b; a >= c; a -= d)
#define ms (a); memset (a, 0, sizeof a);
#define imax INT_MAX
#define imin INT_MIN
#define wh(a) while (a --)
using namespace std;
int t, n;
signed main () {
	cout << fixed << setprecision (5);
	cin >> t;
	wh (t) {
		cin >> n;
		bool flag = 0;
		for (int i = max (2ll, (int) pow (n, 1 / 2.00) - 5); i <= max (2ll, (int) pow (n, 1 / 2.00) + 5); i ++) if (i * i + i + 1 == n) flag = 1;
		for (int i = max (2ll, (int) pow (n, 1 / 3.00) - 5); i <= max (2ll, (int) pow (n, 1 / 3.00) + 5); i ++) if (i * i * i + i * i + i + 1 == n) flag = 1;
		for (int i = max (2ll, (int) pow (n, 1 / 4.00) - 5); i <= max (2ll, (int) pow (n, 1 / 4.00) + 5); i ++) if (i * i * i * i + i * i * i + i * i + i + 1 == n) flag = 1;
		for (int i = max (2ll, (int) pow (n, 1 / 5.00) - 5); i <= max (2ll, (int) pow (n, 1 / 5.00) + 5); i ++) if (i * i * i * i * i + i * i * i * i + i * i * i + i * i + i + 1 == n) flag = 1;
		for (int i = 2; i <= 3000; i ++) {
			int n1 = n, res = 0, fl = 1;
			while (n1 != 1) {
				n1 --;
				if (n1 % i == 0) res ++, n1 /= i;
				else {
					fl = 0;
					break;
				}
			}
			if (fl == 1 && res > 1) flag = 1;
		}
		if (flag) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}