#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int findKeyByNumber(int n, int m, int num) {
	int key = 0;
	for (int col = 1;col <= m;col++) {
		int l = 1, r = n;
		for (int cc = 0;cc<40;cc++) {
			int mid = (l + r) / 2;
			if (mid*col>num) {
				r = mid - 1;
			}
			else
				l = mid;
		}
		if (r*col <= num)
			key += r;
		else
			key += l;
	}
	return key;
}

int findKeyByNumberBrute(int n, int m, int num) {
	vector<int> all;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			all.push_back(i*j);
		}
	}
	sort(all.begin(), all.end());
	for (int i = all.size() - 1;i >= 0;i--) {
		if (all[i] == num)
			return i + 1;
	}
	return -1;
}
int n, m, k;

void input1() {
	cin >> n >> m >> k;
}


signed main()
{
	input1();
	int l = 1, r = n*m;
	while (r-l>1) {
		int mid = (l + r) / 2;
		cerr << "mid = " << mid << "\n";
		int currKey = findKeyByNumber(n, m, mid);
		if (k<currKey) {
			r = mid - 1;
		}
		else {
			l = mid;
		}
	}
	for (int x = max(1, l - 10);x <= min(n*m, l + 10);x++) {

		int currKey = findKeyByNumber(n, m, x);
		if (currKey >= k) {
			cout << x;
			//system("pause");///!
			exit(0);
		}
	}
	return 0;
}















