#include<bits/stdc++.h>
using namespace std;


long long root_n(long long n, int k)
{
	long long m = pow(n, (long double)1.0 / k);
	while (pow(m, k) <= n) 
    m++;
	m--;
	return m;
}

void solve()
{
  long long n;
	cin >> n;


	for (int m = 3; m<65;++m)
    {
		long long k = root_n(n, m-1);
		if (k < 2) continue;
		__int128 nn = n;
		nn *= (k - 1);
		nn += 1;
		while (nn % k == 0) nn /= k;
		if (nn == 1) {
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
	return;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}
