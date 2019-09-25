#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
using namespace std;
typedef long long ll;
ll findKeyByNumber(int& n, int& m, ll& num) {
	ll key = 0;
	for (int col = 1;col <= m;++col) {
		int l = 1, r = n;
		while (r - l>1) {
			int mid = (l + r) >> 1;
			if (1ll * mid*col>num) {
				r = mid - 1;
			}
			else
				l = mid;
		}
		if (r*col <= num)
			key += r;
		else if(l*col<=num)
			key += l;
	}
	return key;
}

int findKeyByNumberBrute(int n, int m, int num) {
	vector<int> all;
	for (int i = 1;i <= n;++i) {
		for (int j = 1;j <= m;++j) {
			all.push_back(i*j);
		}
	}
	sort(all.begin(), all.end());
	for (int i = all.size() - 1;i >= 0;--i) {
		if (all[i] == num)
			return i + 1;
	}
	return -1;
}

void input1(int &n, int &m, ll &k) {
	cin >> n >> m >> k;
}
ll solveFast(int n, int m, ll k) {
	ll l = 1, r = (ll)n*m;
	while (r - l>1ll) {
		ll mid = (l + r) >> 1ll;
		ll currKey = findKeyByNumber(n, m, mid);
		if (currKey >= k) {
			r = mid - 1ll;
		}
		else {
			l = mid;
		}
	}
	ll mff = min((ll)n*m, l + 10ll);
	ll strt = max(1ll, l - 10ll);
	for (ll x = strt;x <= mff;++x) {
		ll currKey = findKeyByNumber(n, m, x);
		if (currKey >= k) {
			return x;
		}
	}
	return -1ll;
}

ll solveSlow(int n, int m, int k) {
	vector<int> all;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			all.push_back(i*j);
		}
	}
	sort(all.begin(), all.end());
	return all[k - 1ll];
}

void input2(int& n, int& m) {
	mt19937 X(chrono::steady_clock::now().time_since_epoch().count());
	n = X() % 100 + 1;
	m = X() % 100 + 1;
}
ofstream out("output.txt");
signed main()
{
	int n, m;
	ll k;
	input1(n, m, k);
	cout << solveFast(n, m, k) << "\n";
	//system("pause");
	return 0;
	/*cout << solveFast(n, m, k) << " " << solveSlow(n, m, k)<<"\n";
	return 0;
	int cnt = 0;
	for(int n=1;n<=100;n++) {
	for (int m = 1;m <= 100;m++) {
	//input2(n, m);
	for (int k = 1;k <= n*m;k++) {
	int sl = solveSlow(n, m, k);
	int fa = solveFast(n, m, k);
	if (sl != fa) {
	out << n << " " << m << " " << k << "\n";
	exit(0);
	}
	cnt++;
	if (cnt == 1000)
	{
	cerr << ".";
	cnt = 0;
	}
	}
	}
	}*/
}















